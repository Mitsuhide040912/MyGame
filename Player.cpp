#define NOMINMAX
#include <Windows.h>
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Field.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include "Item.h"
#include "Engine/SceneManager.h"
#include "GoalFrag.h"
#include "Enemy.h"
#include <DirectXMath.h>
#include <algorithm>


#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

using namespace DirectX;

//�J�����̎w��
enum CAM_TYPE
{
	//FIXED_TYPE, //�Œ�̎��_
	TPS_NORT_TYPE,//�O�l�̉�]�Ȃ�
	TPS_TYPE,//�O�l�̉�]����
	FPS_TYPE,//��l��
	MAX_TYPE//�����A��o������I���
};

//�A�j���[�V�����̎w��
enum ANM_TYPE
{
	WAIT = 0,
	RUN,
	PICK,
	MAX
};

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1),
	speed_(0.05),
	front_({ 0,0,1,0 }), 
	camState_(CAM_TYPE::TPS_NORT_TYPE),
	isItem_(false),isGoal_(false)
{

	//static const std::string filemename[MAX] = { "Running.fbx" };
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModelanime_[0] = Model::Load("Model\\Idle.fbx");
	hModelanime_[1] = Model::Load("Model\\Running.fbx");
	hModelanime_[2] = Model::Load("Model\\pickup.fbx");
	hModel_ = hModelanime_[0];

	speed_ = 0.2;
	float_ = XMVECTOR({ 0,0,1,0 });
	transform_.scale_ = { 2,2,2 };
	transform_.position_.x = -35;
	//transform_.position_.x = -35;
	transform_.position_.z = 30;
	//transform_.rotate_.y = 180.0f;

	//SphereCollider* Collision = new SphereCollider(XMFLOAT3(0, 2, 0), 1.2f);
	//AddCollider(Collision);

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 1, 0), XMFLOAT3(1, 5, 1));
	AddCollider(collision);
	
	//animType_ = (ANM_TYPE::WAIT);
	//���ҋ@���[�V�����̃t���[���Ǘ�
	Model::SetAnimFrame(hModelanime_[0], 1, 310, 1);
	//�������A�j���[�V�����̃t���[���Ǘ�
	Model::SetAnimFrame(hModelanime_[1], 1, 50, 1);
	//���A�j���[�V�����̃t���[���Ǘ�
	Model::SetAnimFrame(hModelanime_[2], 1, 65, 1);
}


void Player::Update()
{
	

	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR move{ 0,0,0,0 };
	XMVECTOR rotVec{ 0,0,0,0 };
	float dir = 0;
	
	switch (animType_)
	{
	case ANM_TYPE::WAIT:
		hModel_ = hModelanime_[0];
		break;
	case ANM_TYPE::RUN:
		hModel_ = hModelanime_[1];
		break;
	case ANM_TYPE::PICK:
		hModel_ = hModelanime_[2];
		break;
	default:
		break;
	}

	//�O�i
	if (Input::IsKey(DIK_W))
	{
		animType_ = ANM_TYPE::RUN;
		dir = 1.0;
	}
	else
	{
		animType_ = ANM_TYPE::WAIT;
	}
	//���
	if (Input::IsKey(DIK_S))
	{
		animType_ = ANM_TYPE::RUN;
		dir = -1.0;
	}
	//�����Ƃ�A�j���[�V����
	if (Input::IsKey(DIK_J))
	{
		animType_ = ANM_TYPE::PICK;
	}
	//����]
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 2.0f;
	}
	//�E��]
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 2.0f;
	}
	//�����L�[��������Ă��Ȃ�������WAIT���Ă�
	else if (!Input::IsKey)
	{
		animType_ = ANM_TYPE::WAIT;
	}
	//���R���g���[���[�̏�����ǉ�����
	//transform_.position_ = Input::GetPadStickL();


	//��]�s��
	rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//�x�N�g���̉�]����
	rotVec = XMVector3TransformCoord(front_, rotY);
	move = speed_ * rotVec;
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + dir * move;
	XMStoreFloat3(&(transform_.position_), pos);

	//transform_.position_.x = std::clamp(transform_.position_.x, -28.0f, 28.0f);//���v���C���[���������Ɉ�苗���ȊO�ɒB������o�Ȃ��悤��
	//transform_.position_.z = std::clamp(transform_.position_.z, -12.0f, 80.0f);//���v���C���[���������Ɉ�苗���ȊO�ɒB������o�Ȃ��悤��
	transform_.position_.x = std::clamp(transform_.position_.x, -100.0f, 100.0f);//���v���C���[���������Ɉ�苗���ȊO�ɒB������o�Ȃ��悤��
	transform_.position_.z = std::clamp(transform_.position_.z, -100.0f, 100.0f);//���v���C���[���������Ɉ�苗���ȊO�ɒB������o�Ȃ��悤��
	//�����������n�ʂƂ̓����蔻��
	Field* pGround = (Field*)FindObject("Field");
	int hGmodel = pGround->GetModelHandle();
	//���C�L���X�g
	RayCastData data;
	data.start = transform_.position_;
	data.start.y += 4;
	data.dir = XMFLOAT3({ 0,-1,0 });
	Model::RayCast(hGmodel, &data);

	//RayCastData head;
	//head.start = transform_.position_;
	//head.dir = XMFLOAT3(0, 1, 0);
	//head.start.y += 0.1f;
	//Model::RayCast(hGmodel, &head);

	//if (head.hit && head.dist < 10.0f)
	//{
	//	float allowdHaight = head.start.y + head.dist - 10.0f;
	//	transform_.position_.y = std::min(transform_.position_.y, allowdHaight);
	//}

	if (data.hit)
	{
		transform_.position_.y -= data.dist - 4;
	}


	//�J�����̕\���ύX
	if (Input::IsKeyDown(DIK_Z))
	{
		camState_++;
		if (camState_ == CAM_TYPE::MAX_TYPE)camState_ = CAM_TYPE::TPS_NORT_TYPE;
	}

	switch (camState_)
	{
	//case CAM_TYPE::FIXED_TYPE://�Œ�
	//{
	//	Camera::SetPosition(XMFLOAT3(0, 10, -120));
	//	Camera::SetTarget(XMFLOAT3(0, -30, 0));
	//	break;
	//}

	case CAM_TYPE::TPS_NORT_TYPE://�኱�ォ�猩�����Ă���J����
	{
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = transform_.position_.y + 15.0f;
		camPos.z = transform_.position_.z - 10.0f;
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
		break;
	}

	case CAM_TYPE::TPS_TYPE://TPS���_
	{
		//XMFLOAT3 camtar = transform_.position_;
		//camtar.y += 2.64;
		////camtar.x = 0.8;
		//Camera::SetTarget(camtar);
		//XMFLOAT3 camPos = transform_.position_;
		//XMVECTOR vEye = { 0,2.70,-3,0 };
		//vEye = XMVector3TransformCoord(vEye, rotY);
		//XMStoreFloat3(&camPos, pos + vEye);
		//Camera::SetPosition(camPos);
		//break;
		XMVECTOR camOff = { 0,1,2 };
		camOff = XMVector3TransformCoord(camOff, rotY);

		XMFLOAT3 camtar;
		XMStoreFloat3(&camtar, pos + camOff);
		Camera::SetTarget(camtar);
		//		Camera::SetPosition(camPos);
		//		XMFLOAT3 camtar = transform_.position_;
//		camtar.y += 2.64;

		//camtar.x = 0.8;
//		Camera::SetTarget(camtar);
		XMFLOAT3 camPos = transform_.position_;
		XMVECTOR vEye = { 2,3.50,-3,0 };
		vEye = XMVector3TransformCoord(vEye, rotY);
		XMStoreFloat3(&camPos, pos + vEye);
		Camera::SetPosition(camPos);
		break;
	}

	case CAM_TYPE::FPS_TYPE://�P�l�̎��_
	{
		XMFLOAT3 fpspos = { transform_.position_.x,transform_.position_.y + 4,transform_.position_.z };
		Camera::SetPosition(fpspos);
		XMFLOAT3 camTarget;
		XMVECTOR campos = XMLoadFloat3(&fpspos);
		XMStoreFloat3(&camTarget, campos + move);
		Camera::SetTarget(camTarget);
		break;
	}
	default:
		break;
	}
	GoalFrag* gf = (GoalFrag*)FindObject("GoalFrag");
	if (gf)
	{
		XMFLOAT3 goalPos = gf->GetPosition();
		float distance = XMVectorGetX(XMVector3Length(XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&goalPos)));
		if (distance > 1.0f)
		{
			isGoal_ = false;//��isGoal��false�ɂ��ăS�[�����Ȃ�
		}
	}

	if (isItem_ && isGoal_){//��isItem���擾����isGoal���擾����ăS�[���t���b�O�ɐG���ƃN���A
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
        sm->ChangeScene(SCENE_ID_CLEAR);
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	ImGui::Text("PositionX:%.3f", transform_.position_.x);
	ImGui::Text("PositionY:%.3f", transform_.position_.y);
	ImGui::Text("PositionZ:%.3f", transform_.position_.z);
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{

	if (pTarget->GetObjectName() == "Item"){
		XMFLOAT3 posChange = transform_.position_;
		posChange.y = transform_.position_.y + 3.0f;
	    pTarget->SetPosition(posChange);
	    isItem_ = true;//��isItem��true�ɂ��Ď擾
		//SceneManager* cr = (SceneManager*)FindObject("SceneManager");
		//cr->ChangeScene(SCENE_ID_CLEAR);
		//KillMe();
	}
	if (pTarget->GetObjectName() == "GoalFrag") {
		
		isGoal_ = true;//��isGoal��true�ɂ��Ď擾

		//SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		//sm->ChangeScene(SCENE_ID_CLEAR);
	}
	if (pTarget->GetObjectName() == "Enemy") {
		SceneManager* ov = (SceneManager*)FindObject("SceneManager");
		ov->ChangeScene(SCENE_ID_CLEAR);
	}
}

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

//カメラの指定
enum CAM_TYPE
{
	//FIXED_TYPE, //固定の視点
	TPS_NORT_TYPE,//三人称回転なし
	TPS_TYPE,//三人称回転あり
	FPS_TYPE,//一人称
	MAX_TYPE//ここ、空出来たら終わり
};

//アニメーションの指定
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
	//↓待機モーションのフレーム管理
	Model::SetAnimFrame(hModelanime_[0], 1, 310, 1);
	//↓ランアニメーションのフレーム管理
	Model::SetAnimFrame(hModelanime_[1], 1, 50, 1);
	//取るアニメーションのフレーム管理
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

	//前進
	if (Input::IsKey(DIK_W))
	{
		animType_ = ANM_TYPE::RUN;
		dir = 1.0;
	}
	else
	{
		animType_ = ANM_TYPE::WAIT;
	}
	//後退
	if (Input::IsKey(DIK_S))
	{
		animType_ = ANM_TYPE::RUN;
		dir = -1.0;
	}
	//物をとるアニメーション
	if (Input::IsKey(DIK_J))
	{
		animType_ = ANM_TYPE::PICK;
	}
	//左回転
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 2.0f;
	}
	//右回転
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 2.0f;
	}
	//何もキーが押されていなかったらWAITを呼ぶ
	else if (!Input::IsKey)
	{
		animType_ = ANM_TYPE::WAIT;
	}
	//↓コントローラーの処理を追加する
	//transform_.position_ = Input::GetPadStickL();


	//回転行列
	rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//ベクトルの回転結果
	rotVec = XMVector3TransformCoord(front_, rotY);
	move = speed_ * rotVec;
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + dir * move;
	XMStoreFloat3(&(transform_.position_), pos);

	//transform_.position_.x = std::clamp(transform_.position_.x, -28.0f, 28.0f);//←プレイヤーが横方向に一定距離以外に達したら出ないように
	//transform_.position_.z = std::clamp(transform_.position_.z, -12.0f, 80.0f);//←プレイヤーが奥方向に一定距離以外に達したら出ないように
	transform_.position_.x = std::clamp(transform_.position_.x, -100.0f, 100.0f);//←プレイヤーが横方向に一定距離以外に達したら出ないように
	transform_.position_.z = std::clamp(transform_.position_.z, -100.0f, 100.0f);//←プレイヤーが奥方向に一定距離以外に達したら出ないように
	//↓いちおう地面との当たり判定
	Field* pGround = (Field*)FindObject("Field");
	int hGmodel = pGround->GetModelHandle();
	//レイキャスト
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


	//カメラの表示変更
	if (Input::IsKeyDown(DIK_Z))
	{
		camState_++;
		if (camState_ == CAM_TYPE::MAX_TYPE)camState_ = CAM_TYPE::TPS_NORT_TYPE;
	}

	switch (camState_)
	{
	//case CAM_TYPE::FIXED_TYPE://固定
	//{
	//	Camera::SetPosition(XMFLOAT3(0, 10, -120));
	//	Camera::SetTarget(XMFLOAT3(0, -30, 0));
	//	break;
	//}

	case CAM_TYPE::TPS_NORT_TYPE://若干上から見たついてくるカメラ
	{
		XMFLOAT3 camPos = transform_.position_;
		camPos.y = transform_.position_.y + 15.0f;
		camPos.z = transform_.position_.z - 10.0f;
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
		break;
	}

	case CAM_TYPE::TPS_TYPE://TPS視点
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

	case CAM_TYPE::FPS_TYPE://１人称視点
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
			isGoal_ = false;//←isGoalをfalseにしてゴールしない
		}
	}

	if (isItem_ && isGoal_){//←isItemを取得かつisGoalが取得されてゴールフラッグに触れるとクリア
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
	    isItem_ = true;//←isItemをtrueにして取得
		//SceneManager* cr = (SceneManager*)FindObject("SceneManager");
		//cr->ChangeScene(SCENE_ID_CLEAR);
		//KillMe();
	}
	if (pTarget->GetObjectName() == "GoalFrag") {
		
		isGoal_ = true;//←isGoalをtrueにして取得

		//SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		//sm->ChangeScene(SCENE_ID_CLEAR);
	}
	if (pTarget->GetObjectName() == "Enemy") {
		SceneManager* ov = (SceneManager*)FindObject("SceneManager");
		ov->ChangeScene(SCENE_ID_CLEAR);
	}
}

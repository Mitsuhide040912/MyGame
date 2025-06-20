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
#include <cmath>
#include "Engine/time.h"


#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

using namespace DirectX;

//カメラの指定
enum CAM_TYPE
{
	TPS_TYPE,//三人称回転あり
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
	:GameObject(parent, "Player")
	,hModel_(-1)
	,speed_(0.05)
	,front_({ 0,0,1,0 })
	,camState_(CAM_TYPE::TPS_TYPE)
	,isItem_(false)
	,isGoal_(false),fall_(0),thisFall_(false),prevDist_(9999),canMove_(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModelanime_[0] = Model::Load("Model\\Idle.fbx");
	assert(hModelanime_[0] >= 0);
	hModelanime_[1] = Model::Load("Model\\Running.fbx");
	assert(hModelanime_[1] >= 1);
	hModelanime_[2] = Model::Load("Model\\pickup.fbx");
	assert(hModelanime_[2] >= 2);
	speed_ = 0.3;
	//transform_.rotate_.y = 90;
	transform_.scale_ = { 3.5,3.5,3.5 };
	transform_.position_ = { -20,0,-50 };


	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 3, 0), XMFLOAT3(1, 5, 1));
	AddCollider(collision);


	
	//↓待機モーションのフレーム管理
	Model::SetAnimFrame(hModelanime_[0], ANIM_STRT_FRAME, ANIM_Idle_FRAME, ANIM_END_SPEED);
	//↓ランアニメーションのフレーム管理
	Model::SetAnimFrame(hModelanime_[1], ANIM_STRT_FRAME, ANMI_Running_FRAME, ANIM_END_SPEED);
	//取るアニメーションのフレーム管理
	Model::SetAnimFrame(hModelanime_[2], ANIM_STRT_FRAME, ANIM_Pickup_FRAME, ANIM_END_SPEED);
}


void Player::Update()
{
	//XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	XMVECTOR move{ 0,0,0,0 };
	XMVECTOR rotVecY{ 0,0,0,0 };
	XMVECTOR rotVecX{ 0,0,0,0 };
	XMFLOAT3 stickL = Input::GetPadStickL();
	XMFLOAT3 stickR = Input::GetPadStickR();
	const int SPEED = 60;
	float dir;
	dir = 0.0f;


	dir += (float) dir/1000.0f * (speed_ * Time::DeltaTime());

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

	if (thisFall_ != true) {
		//前進
		if (Input::IsKey(DIK_W) || stickL.y > 0.3f)//コントローラーの実装もした
		{
			animType_ = ANM_TYPE::RUN;
			dir = SPEED * Time::DeltaTime();
			//dir = 1.0;
		}
		else
		{
			animType_ = ANM_TYPE::WAIT;
		}
		//後退
		if (Input::IsKey(DIK_S) || stickL.y < -0.3f)//コントローラーの実装もした
		{
			animType_ = ANM_TYPE::RUN;
			dir = -SPEED * Time::DeltaTime();
			//dir = -1.0;
		}
	}
	else
	{
		animType_ = ANM_TYPE::WAIT;
	}
	//物をとるアニメーション
	if (Input::IsKey(DIK_J) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		animType_ = ANM_TYPE::PICK;
	}
	//左回転
	if (Input::IsKey(DIK_A) || stickR.x < -0.3)//コントローラーの実装もした
	{
		transform_.rotate_.y -= 2.0f;
	}
	//右回転
	if (Input::IsKey(DIK_D) || stickR.x > 0.3f)//コントローラーの実装もした
	{
		transform_.rotate_.y += 2.0f;
	}

	//回転行列Y
	rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//ベクトルの回転結果
	rotVecY = XMVector3TransformCoord(front_, rotY);
	move = speed_ * rotVecY;
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + dir * move;

	XMStoreFloat3(&(transform_.position_), pos);

	transform_.position_.x = std::clamp(transform_.position_.x, -300.0f, 300.0f);//←プレイヤーが横方向に一定距離以外に達したら出ないように
	transform_.position_.z = std::clamp(transform_.position_.z, -300.0f, 300.0f);//←プレイヤーが奥方向に一定距離以外に達したら出ないように
	//↓いちおう地面との当たり判定
	Field* pGround = (Field*)FindObject("Field");
	int hGmodel = pGround->GetModelHandle();
	//レイキャスト
	RayCastData data;
	data.start = transform_.position_;
	data.start.y += 4;
	data.dir = XMFLOAT3({ 0,-1,0 });
	Model::RayCast(hGmodel, &data);
	if (!thisFall_)
	{
		if (data.hit)
		{
			if (prevDist_ < data.dist - 4)
			{
				fallDist_ = data.dist - 4;
				thisFall_ = true;
				fallTime = fallDist_ / 15;
			}
			else
			{
				transform_.position_.y -= data.dist - 4;
				prevDist_ = data.dist;
			}

		}
	}
	else
	{
		if (fallTime > 0)
		{
			Fall();
		}
		else
		{
			thisFall_ = false;
		}
	}

	//カメラの表示変更
	if (Input::IsKeyDown(DIK_Z) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		camState_++;
		if (camState_ == CAM_TYPE::MAX_TYPE)camState_ = CAM_TYPE::TPS_TYPE;
	}

	switch (camState_)
	{
	case CAM_TYPE::TPS_TYPE://TPS視点
	{
		XMVECTOR camOff = { 0,4,3 };
		camOff = XMVector3TransformCoord(camOff, rotY);

		XMFLOAT3 camtar;
		XMStoreFloat3(&camtar, pos + camOff);
		Camera::SetTarget(camtar);
		XMFLOAT3 camPos = transform_.position_;
		XMVECTOR vEye = { 0,5,-12 };
		vEye = XMVector3TransformCoord(vEye, rotY);
		XMStoreFloat3(&camPos, pos + vEye);
		Camera::SetPosition(camPos);
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

	if (isItem_ && isGoal_) {//←isItemを取得かつプレイヤーがゴールフラッグに触れるとクリア
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_CLEAR);
	}

	if (CarryItem != nullptr) {
		
		XMFLOAT3 itemPos = { transform_.position_.x,
			transform_.position_.y + 5.0f,
			transform_.position_.z + 0.0f };
		XMFLOAT3 itemRot = { transform_.rotate_.x,transform_.rotate_.y,transform_.rotate_.z };
		CarryItem->SetTransform(itemPos, itemRot);
	}
	//↓yが-150を超えた時点でゲームオーバー
	if (transform_.position_.y < -157.0f) {
		KillMe();
		SceneManager* sm = (SceneManager*)FindObject("SceneManager");
		sm->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

void Player::OnCollision(GameObject* pTarget)
{

	if (pTarget->GetObjectName() == "Item") {
		CarryItem = dynamic_cast<Item*>(pTarget);
		//XMFLOAT3 posChange = transform_.position_;
		//posChange.y = transform_.position_.y + 3.0f;
		//posChange.z = transform_.position_.z + 1.0f;
		//if (isItem_) {
		//	XMVECTOR rotVecY = XMVector3TransformCoord(front_, rotY);
		//	XMVECTOR pos = XMLoadFloat3(&(posChange));
		//	
		//	XMVECTOR move = speed_ * rotVecY;
		//	pos = pos + itemDir * move;

		//	XMStoreFloat3(&(posChange), pos);
		//	pTarget->SetPosition(posChange);
		//	
		//}
		isItem_ = true;
	}
	if (pTarget->GetObjectName() == "GoalFrag") {

		isGoal_ = true;//←isGoalをtrueにして取得
	}
	if (pTarget->GetObjectName() == "Enemy") {
		SceneManager* ov = (SceneManager*)FindObject("SceneManager");
		ov->ChangeScene(SCENE_ID_GAMEOVER);
	}
}

void Player::Fall()
{
	transform_.position_.y -= 15 * Time::DeltaTime();
	fallTime -= Time::DeltaTime();
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







#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Field.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"

//カメラの指定
enum CAM_TYPE
{
	FIXED_TYPE, //固定の視点
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
	MAX
};

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1),
	speed_(0.05), front_({ 0,0,1,0 }), camState_(CAM_TYPE::FIXED_TYPE)
{

	//static const std::string filemename[MAX] = { "Running.fbx" };
}

Player::~Player()
{
}

void Player::Initialize()
{
	//hModel_ = Model::Load("Model\\Standing.fbx");
	//assert(hModel_ >= 0);
	//hModel_ = Model::Load("Model\\Running.fbx");
	//assert(hModel_ >= 0);
	
	hModelanime_[0]= Model::Load("Model\\Idle.fbx");
	hModelanime_[1] = Model::Load("Model\\Running.fbx");
	hModel_ = hModelanime_[0];

	speed_ = 0.15;
	float_ = XMVECTOR({ 0,0,1,0 });
	transform_.scale_ = { 2,2,2 };
	transform_.position_.z = -100;

	//animType_ = (ANM_TYPE::WAIT);
	//↓待機モーション
	Model::SetAnimFrame(hModelanime_[0], 1, 311, 1);
	//↓ランアニメーションのフレーム実装
	Model::SetAnimFrame(hModelanime_[1], 1, 50, 1);
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
	default:
		break;
	}

	//前進
	if (Input::IsKey(DIK_W))
	{

		animType_ = ANM_TYPE::RUN;
		XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		XMVECTOR rotVec = XMVector3TransformCoord(float_, rotY);

		XMVECTOR move;
		move = speed_ * rotVec;
		XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
		pos = pos + move;
		XMStoreFloat3(&(transform_.position_), pos);
	}
	else
	{
		animType_ = ANM_TYPE::WAIT;
	}

	//後退
	if (Input::IsKey(DIK_S))
	{
		animType_ = ANM_TYPE::RUN;
		XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
		XMVECTOR rotVec = XMVector3TransformCoord(float_, rotY);

		XMVECTOR move;
		move = speed_ * rotVec;
		XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
		pos = pos - move;
		XMStoreFloat3(&(transform_.position_), pos);
	}


#if 1
	if (Input::IsKey(DIK_A))
	{
		transform_.rotate_.y -= 2.0f;
	}
	if (Input::IsKey(DIK_D))
	{
		transform_.rotate_.y += 2.0f;
	}
	else if (!Input::IsKey)
	{
		animType_ = ANM_TYPE::WAIT;
	}
#endif

	//回転行列
	rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	//ベクトルの回転結果
	rotVec = XMVector3TransformCoord(front_, rotY);
	move = speed_ * rotVec;
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + dir * move;
	XMStoreFloat3(&(transform_.position_), pos);
	//↓いちおう地面との当たり判定
	Field* pGround = (Field*)FindObject("Field");
	int hGmodel = pGround->GetModelHandle();
	//レイキャスト
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0;
	data.dir = XMFLOAT3({ 0,-1,0 });
	Model::RayCast(hGmodel, &data);

	if (data.hit == true)
	{
		transform_.position_.y = -data.dist;
	}
	//カメラの表示変更
	if (Input::IsKeyDown(DIK_Z))
	{
		camState_++;
		if (camState_ == CAM_TYPE::MAX_TYPE)camState_ = CAM_TYPE::FIXED_TYPE;
	}

	switch (camState_)
	{
	case CAM_TYPE::FIXED_TYPE://固定
	{
		Camera::SetPosition(XMFLOAT3(0, 10, -120));
		Camera::SetTarget(XMFLOAT3(0, -30, 0));
		break;
	}

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
		Camera::SetTarget(transform_.position_);
		XMVECTOR vEye{ 0,3,-10,-10 };
		vEye = XMVector3TransformCoord(vEye, rotY);
		XMFLOAT3 camPos;
		XMStoreFloat3(&camPos, pos + vEye);
		Camera::SetPosition(camPos);
		break;
	}

	case CAM_TYPE::FPS_TYPE://１人称視点
	{
		XMFLOAT3 fpspos = { transform_.position_.x,transform_.position_.y + 3,transform_.position_.z };
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

}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}

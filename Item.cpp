#include "Item.h"
#include "Field.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include"Engine/SceneManager.h"
Item::Item(GameObject* parent)
	:GameObject(parent,"Item"),hModel_(-1)
{
}

Item::~Item()
{
}

void Item::Initialize()
{
	hModel_ = Model::Load("Model\\egg.fbx");
	assert(hModel_ > 0);
	transform_.position_.x = -79;
	transform_.position_.y = -107;
	transform_.position_.z = 210;
	transform_.scale_ = { 1,1,1 };
	//SphereCollider* Collision = new SphereCollider(XMFLOAT3(0, 1, 0), 1.2f);
	//AddCollider(Collision);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 1, 0), XMFLOAT3(2, 2, 2));
	AddCollider(collision);
}

void Item::Update()
{
	XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
	XMVECTOR move   { 0,0,0,0 };
	XMVECTOR rotVecY{ 0,0,0,0 };
	XMVECTOR rotVecX{ 0,0,0,0 };
	float dir = 0;
	rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	rotVecY = XMVector3TransformCoord(front_, rotY);
	move = speed_ * rotVecY;
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + dir * move;
	XMStoreFloat3(&(transform_.position_), pos);


	//↓地面との判定
	Field* pGround = (Field*)FindObject("Field");
	int hGmodel = pGround->GetModelHandle();
	//レイキャスト
	RayCastData data;
	data.start = transform_.position_;
	data.start.y += 4;
	data.dir = XMFLOAT3({ 0,-1,0 });
	Model::RayCast(hGmodel, &data);

	if (data.hit)
	{
		transform_.position_.y -= data.dist - 4;
	}
}

void Item::OnCollision(GameObject* pTarget)
{
	//if (pTarget->GetObjectName() == "Player")
	//{
	//	SceneManager* cr = (SceneManager*)FindObject("SceneManager");
	//	cr->ChangeScene(SCENE_ID_CLEAR);
	//	KillMe();
	//}
}

void Item::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

}

void Item::Release()
{
}



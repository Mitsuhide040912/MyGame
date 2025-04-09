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
	hModel_ = Model::Load("Model\\ItemBox.fbx");
	assert(hModel_ > 0);
	transform_.position_.z = 70.0f;
	transform_.rotate_.y = 180.0f;
	SphereCollider* Collision = new SphereCollider(XMFLOAT3(0, 1, 0), 1.2f);
	AddCollider(Collision);
}

void Item::Update()
{


	//↓地面との判定
	Field* pGround = (Field*)FindObject("Field");
	int hGmodel = pGround->GetModelHandle();
	//レイキャスト
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0;
	data.dir = XMFLOAT3({ 0,-1,0 });
	Model::RayCast(hGmodel, &data);

	if (data.hit)
	{
		transform_.position_.y = -data.dist;
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



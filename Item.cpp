#include "Item.h"
#include "Field.h"
#include "Engine/Model.h"
Item::Item(GameObject* parent)
	:GameObject(parent,"Item"),hModel_(-1)
{
}

Item::~Item()
{
}

void Item::Initialize()
{
	//hModel_ = Model::Load("Model\\ItemBox.fbx");
	hModel_ = Model::Load("Model\\ItemBox.fbx");
	assert(hModel_ > 0);
}

void Item::Update()
{

	transform_.position_.z = 100.0f;
	transform_.rotate_.y = 180.0f;
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

void Item::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Item::Release()
{
}

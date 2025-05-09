#include "GoalFrag.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
#include "Field.h"
#include "Player.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

GoalFrag::GoalFrag(GameObject* parent)
	:GameObject(parent,"GoalFrag"),hModel_(-1)
{
}

void GoalFrag::Initialize()
{
	hModel_ = Model::Load("Model\\GoalFrag.fbx");
	assert(hModel_ >= 0);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 2, 0), XMFLOAT3(1, 1, 1));
	AddCollider(collision);

	transform_.position_ = { x,y,z };
	//transform_.position_.y = 0;
	//transform_.position_.x - 20;
}

void GoalFrag::Update()
{
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

void GoalFrag::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void GoalFrag::Release()
{
}

void GoalFrag::OnCollision(GameObject* pTarget)
{
	
}

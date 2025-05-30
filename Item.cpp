#include "Item.h"
#include "Field.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include"Engine/SceneManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
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
	transform_.position_ = { -75.0,0,160.0 };
	transform_.scale_ = { 0.8,0.8,0.8 };
	//SphereCollider* Collision = new SphereCollider(XMFLOAT3(0, 1, 0), 1.2f);
	//AddCollider(Collision);
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 1, 0), XMFLOAT3(2, 2, 2));
	AddCollider(collision);
}

void Item::Update()
{
	Player* iPlayer = (Player*)FindObject("Player");
	if (!iPlayer->GetItemState()) {
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

}

void Item::OnCollision(GameObject* pTarget)
{
}

void Item::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	static float pos[3] = { x,y,z };
	if (ImGui::InputFloat3("ItemPos:%.3f", pos))
	{
		transform_.position_ = { pos[0], pos[1], pos[2] };
	}
}

void Item::Release()
{
}



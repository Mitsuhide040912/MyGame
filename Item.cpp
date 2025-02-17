#include "Item.h"
#include"Engine/Model.h"
#include "Player.h"
Item::Item(GameObject* parent)
	:GameObject(parent,"Item"),hModel_(-1)
{
}

Item::~Item()
{
}

void Item::Initialize()
{
	Model::Load("Model\\Present.fbx");
	assert(hModel_ > 0);
}

void Item::Update()
{
}

void Item::Draw()
{
}

void Item::Release()
{
}

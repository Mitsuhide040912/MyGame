#include "Block.h"
#include "Engine/Model.h"

Block::Block(GameObject* parent)
	:GameObject(parent,"Block"),hModel_(-1)
{
}

void Block::Initialize()
{
	hModel_=Model::Load("Model\\Lava.fbx");
	//assert(hModel_ >= 0);
}

void Block::Update()
{
}

void Block::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Block::Release()
{
}

void Block::OnCollision(GameObject* pTarget)
{
}

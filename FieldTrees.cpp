#include "FieldTrees.h"
#include "Engine/Model.h"
FieldTrees::FieldTrees(GameObject* parent)
	:GameObject(parent,"FieldTrees"),hModel_(-1)
{
}

FieldTrees::~FieldTrees()
{
}

void FieldTrees::Initialize()
{
	hModel_ = Model::Load("Model\\Trees.fbx");
	assert(hModel_ >= 0);
	transform_.rotate_.y = 180.0f;
}

void FieldTrees::Update()
{
	transform_.position_.y = -30.0f;
}

void FieldTrees::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void FieldTrees::Release()
{
}

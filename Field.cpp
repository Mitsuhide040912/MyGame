#include "Field.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
Field::Field(GameObject* parent)
	:GameObject(parent, "Field"), hModel_(-1)
{
}

Field::~Field()
{
}

void Field::Initialize()
{
	hModel_ = Model::Load("Model\\Map.fbx");
	assert(hModel_ >= 0);
}

void Field::Update()
{
}

void Field::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Field::Release()
{
}

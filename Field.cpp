#include "Field.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "GoalFrag.h"

#include <string>

using std::string;
using std::to_string;

Field::Field(GameObject* parent)
	:GameObject(parent, "Field"), hModel_(-1)
{
}

Field::~Field()
{
}

void Field::Initialize()
{
	hModel_ = Model::Load("Model\\MyGameStage5000.fbx");
	assert(hModel_ >= 0);
	Instantiate<GoalFrag>(this);
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

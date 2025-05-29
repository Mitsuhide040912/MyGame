#include "Field.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "GoalFrag.h"

#include <string>

using std::string;
using std::to_string;

Field::Field(GameObject* parent)
	:GameObject(parent, "Field"), hModel_(-1),hField_1(-1),hField_2(-1),hField_3(-1),hField_4(-1)
{
	//for (int i = 0; i < 4; i++) {
	//	hField_[i] = -1;
	//}
}

Field::~Field()
{
}

void Field::Initialize()
{
	//string fileName = "Model\\GameMap";
	//for (int i = 0; i < 4; i++)
	//{
	//	hField_[i] = Model::Load((fileName + to_string(i + 1) + ".fbx").c_str());
	//	assert(hField_[i] >= 0 );
	//}
	hModel_ = Model::Load("Model\\MyGameStage5000.fbx");
	//assert(hModel_ > 0);
	//hField_1 = Model::Load("Model\\GameMap1.fbx");
	////assert(hField_1 >= 0);
	//hField_2 = Model::Load("Model\\GameMap2.fbx");
	////assert(hField_2 >= 0);
	//hField_3 = Model::Load("Model\\GameMap3.fbx");
	////assert(hField_3 >= 0);
	//hField_4 = Model::Load("Model\\GameMap4.fbx");
	////assert(hField_4 >= 0);
	//transform_.rotate_.y = 180.0f;
	Instantiate<GoalFrag>(this);
}

void Field::Update()
{
}

void Field::Draw()
{
	//for (int i = 0; i < 4; i++) {
	//	Model::SetTransform(hField_[i], transform_);
	//	Model::Draw(hField_[i]);
	//}
		Model::SetTransform(hModel_, transform_);
	    Model::Draw(hModel_);
	//Model::SetTransform(hField_1, transform_);
	//Model::Draw(hField_1);
	//Model::SetTransform(hField_2, transform_);
	//Model::Draw(hField_2);
	//Model::SetTransform(hField_3, transform_);
	//Model::Draw(hField_3);
	//Model::SetTransform(hField_4, transform_);
	//Model::Draw(hField_4);
}

void Field::Release()
{
}

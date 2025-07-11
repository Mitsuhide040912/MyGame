#include "ManualScene.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

ManualScene::ManualScene(GameObject* parent)
	:GameObject(parent,"ManualScene"), hImege_(-1), select_(0), prevUpKey_(false), prevDownKey_(false)
{
}

void ManualScene::Initialize()
{
	hImege_ = Image::Load("Model\\ManualScene.png");
	assert(hImege_ >= 0);
}

void ManualScene::Update()
{
	if (Input::IsKey(DIK_O) || Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
	{
		SceneManager* ps = (SceneManager*)FindObject("SceneManager");
		ps->ChangeScene(SCENE_ID_PLAY);
	}
}

void ManualScene::Draw()
{
	Image::SetTransform(hImege_, transform_);
	Image::Draw(hImege_);
}

void ManualScene::Release()
{
}

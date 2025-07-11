#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),hImege_(-1),select_(0),prevUpKey_(false),prevDownKey_(false)
{
}

void TitleScene::Initialize()
{
	hImege_ = Image::Load("Model\\EggHunterGameTitle.png");
	assert(hImege_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsKey(DIK_P) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		SceneManager* ps = (SceneManager*)FindObject("SceneManager");
		ps->ChangeScene(SCENE_ID_MANUAL);
	}
}

void TitleScene::Draw()
{
	Image::SetTransform(hImege_, transform_);
	Image::Draw(hImege_);
}

void TitleScene::Release()
{
}

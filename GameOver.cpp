#include "GameOver.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
GameOver::GameOver(GameObject* parent)
	:GameObject(parent,"GameOver"),hImege_(-1)
{
}

void GameOver::Initialize()
{
	hImege_ = Image::Load("Model\\EggHunterGameOver.png");
	assert(hImege_ >= 0);
}

void GameOver::Update()
{
	if (Input::IsKey(DIK_R) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		SceneManager* ps = (SceneManager*)FindObject("SceneManager");
		ps->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameOver::Draw()
{
	Image::SetTransform(hImege_, transform_);
	Image::Draw(hImege_);
}

void GameOver::Release()
{
}

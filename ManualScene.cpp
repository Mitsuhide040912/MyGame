#include "ManualScene.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"
#include "Engine/SceneManager.h"

ManualScene::ManualScene(GameObject* parent)
	:GameObject(parent,"ManualScene")
	, hImege_(-1), select_(0), prevUpKey_(false), prevDownKey_(false), hSound_(-1)
{
}

void ManualScene::Initialize()
{
	hImege_ = Image::Load("Model\\EHM.png");
	assert(hImege_ >= 0);
	//サウンドデータのロード
	hSound_ = Audio::Load("Model\\fanfare.wav");
	assert(hSound_ >= 0);
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

	Audio::Play(hSound_);
}

void ManualScene::Release()
{
}

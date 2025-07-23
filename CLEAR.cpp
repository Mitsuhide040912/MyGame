#include "CLEAR.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
CLEAR::CLEAR(GameObject* parent)
	:GameObject(parent,"CLEAR"),hImege_(-1)
{
}

void CLEAR::Initialize()
{
	hImege_ = Image::Load("Model\\CLEAR2.png");
	assert(hImege_ >= 0);
}

void CLEAR::Update()
{
	if (Input::IsKey(DIK_R) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		SceneManager* ps = (SceneManager*)FindObject("SceneManager");
		ps->ChangeScene(SCENE_ID_TITLE);
	}
}

void CLEAR::Draw()
{
	Image::SetTransform(hImege_, transform_);
	Image::Draw(hImege_);
}

void CLEAR::Release()
{
}

#include "Timer.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

Timer::Timer(GameObject* parent)
	:GameObject(parent,"Timer"), timer_(300.0f), isTimeUp_(false),hImage_(-1)
{
}

void Timer::Initialize()
{
	transform_.position_ = { 0,-10,0 };

	hImage_ = Image::Load("Model\\Number1.png");
	assert(hImage_ >= 0);
	Image::SetRect(hImage_, 512, 380, 51, 63);
}

void Timer::Update()
{
	if (!isTimeUp_)
	{
		timer_ -= 1.0f / 60.0f;
		if (timer_ <= 0)
		{
			timer_ = 0;
			isTimeUp_ = true;
		}
		if (timer_ == 0)
		{
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_CLEAR);
		}

	}

}

void Timer::Draw()
{
	Image::SetTransform(hImage_, transform_);
	Image::Draw(hImage_);
	
}

void Timer::Release()
{
}

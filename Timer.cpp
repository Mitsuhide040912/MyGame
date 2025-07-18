#include "Timer.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/time.h"

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_dx11.h"
//#include "imgui/imgui_impl_win32.h"

Timer::Timer(GameObject* parent)
	:GameObject(parent,"Timer")
	,timer_(300.0f)
	,isTimeUp_(false)
	,hImage_(-1)
	,x(0.7),y(0.7),z(0),tenMin_(0),min_(0),tenSec_(0),sec_(0),oneSec_(1.0f)
{
}

void Timer::Initialize()
{
	hImage_ = Image::Load("Model\\GameNumber.png");
	assert(hImage_ >= 0);

	transform_.position_ = { x,y,z };
}

void Timer::Update()
{
	if (!isTimeUp_)
	{
		if (oneSec_ > 0) 
		{
			oneSec_ -= Time::DeltaTime();
		}
		else
		{
			timer_ -= 1;
			tenMin_ = timer_ / 600;  //10ï™ÇÃà ÇãÅÇﬂÇÈÅBtenMin_Çtimer_Ç©ÇÁ600ïbäÑÇÈ
			int temp_ = timer_ % 600;
			min_ = temp_ / 60;
			temp_ = temp_ % 60;
			tenSec_ = temp_ / 10;
			sec_ = temp_ % 10;
			oneSec_ = 1.0f;
		}
		if (timer_ <= 0)
		{
			timer_ = 0;
			isTimeUp_ = true;
		}
		if (timer_ == 0)
		{
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");
			sm->ChangeScene(SCENE_ID_GAMEOVER);
		}
	}
}

void Timer::Draw()
{
	Transform trs = transform_;
	trs.position_.x = 0.6;
	Image::SetTransform(hImage_, trs);
	Image::SetRect(hImage_, IMAGE_WIDTH * tenMin_, 30, 50, 90);
	Image::Draw(hImage_);
	
	trs.position_.x = 0.7;
	Image::SetTransform(hImage_, trs);
	Image::SetRect(hImage_, IMAGE_WIDTH * min_, 30, 50, 90);
	Image::Draw(hImage_);

	trs.position_.x = 0.8;
	Image::SetTransform(hImage_, trs);
	Image::SetRect(hImage_, IMAGE_WIDTH * tenSec_, 30, 50, 90);
	Image::Draw(hImage_);

	trs.position_.x = 0.9;
	Image::SetTransform(hImage_, trs);
	Image::SetRect(hImage_, IMAGE_WIDTH * sec_, 30, 50, 90);
	Image::Draw(hImage_);

	//static float pos[3] = { x,y,z };
	//if (ImGui::InputFloat3("UI:%.3f", pos))
	//{
	//	transform_.position_ = { pos[0], pos[1], pos[2] };
	//}
	//ImGui::Text("Timer:%.3f", timer_);
	//ImGui::Text("TimerPos:%.3f", transform_.position_.x);
}

void Timer::Release()
{
}

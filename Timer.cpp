#include "Timer.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/time.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

Timer::Timer(GameObject* parent)
	:GameObject(parent,"Timer")
	,timer_(300.0f)
	,isTimeUp_(false)
	,hImage_(-1)
	,x(0.7),y(0.7),z(0)
{
}

void Timer::Initialize()
{
	hImage_ = Image::Load("Model\\Number1.png");
	assert(hImage_ >= 0);

	transform_.position_ = { x,y,z };
}

void Timer::Update()
{
	if (!isTimeUp_)
	{
		timer_ -= Time::DeltaTime();
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
	Image::SetRect(hImage_, 512 / 9, 380 / 6, 512 / 2, 380 / 6);
	Image::Draw(hImage_);
	static float pos[3] = { x,y,z };
	if (ImGui::InputFloat3("UI:%.3f", pos))
	{
		transform_.position_ = { pos[0], pos[1], pos[2] };
	}
	ImGui::Text("Timer:%.3f", timer_);
}

void Timer::Release()
{
}

void Timer::DrawDigit(int digit, float posX, float posY)
{
	//const int digitWidth = 512 / 9;
	//const int digitHeight = 380 / 6;
	//Image::SetRect(hImage_, digitWidth * digit, 0, digitWidth, digitHeight);
	//Transform t;
	//t.position_ = { posX,posY,z };
	//Image::SetTransform(hImage_, t);

	//Image::Draw(hImage_);
}

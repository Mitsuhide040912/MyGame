#include "PlayScene.h"
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "GoalFrag.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

//#include "FieldTrees.h"
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene"),timer_(60.0f),isTimeUp_(false)
{
}

void PlayScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
	Instantiate<Item>(this);
	//Instantiate<FieldTrees>(this);
	Instantiate<Enemy>(this);
	//Instantiate<GoalFrag>(this);
}

void PlayScene::Update()
{
	//if (Input::IsKey(DIK_SPACE))
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

void PlayScene::Draw()
{
	ImGui::Text("Timer:%.3f", timer_);
}

void PlayScene::Release()
{
}

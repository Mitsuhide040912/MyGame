#include "PlayScene.h"
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "GoalFrag.h"
#include "Timer.h"
#include "Block.h"
#include "Goblin.h"
#include "Bullet.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Model.h"

//#include "imgui/imgui.h"
//#include "imgui/imgui_impl_dx11.h"
//#include "imgui/imgui_impl_win32.h"
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
	Instantiate<Item>(this);
	//Instantiate<Enemy>(this);
	std::vector<Goblin*>goblins;
	XMFLOAT3 goblinPositions[5] = {
		{ 110.0f,   -20.0f, -50.0f },
		{ 100.0f,   -20.0f, -70.0f },
		{ 30.0f,   -20.0f, -50.0f },
		{ 100.0f,   -20.0f,  50.0f },
		{-20.0f,   -20.0f,  40.0f }
	};
	for (int i = 0;i < 5;i++) {
		Goblin* goblin = Instantiate<Goblin>(this);
		goblin->SetPosition(goblinPositions[i]);
	}
	Instantiate<Timer>(this);
}

void PlayScene::Update()
{

}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

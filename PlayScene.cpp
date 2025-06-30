#include "PlayScene.h"
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "GoalFrag.h"
#include "Timer.h"
#include "Block.h"
#include "Goblin.h"
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
	Instantiate<Block>(this);
	Instantiate<Player>(this);
	Instantiate<Item>(this);
	Instantiate<Enemy>(this);



	std::vector<Goblin*>goblins;
	for (int i = 0;i < 20; i++)
	{
		GameObject* goblin = Instantiate<Goblin>(this);
		float x = (rand() %  141)-18;
		float y = goblin->GetPosition().y;
		float z = (rand() % 96)-68;
		goblin->SetPosition({ x,y,z });
		//goblins.push_back(goblin);
	}

	//for (int j = 0;j < 15;j++)
	//{
	//	GameObject* goblin = Instantiate<Goblin>(this);
	//	float x = rand() % 266 - 70;
	//	float y = goblin->GetPosition().y;
	//	float z = -(rand() % 126) - 4;
	//	goblin->SetPosition({ x,y,z });
	//}



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

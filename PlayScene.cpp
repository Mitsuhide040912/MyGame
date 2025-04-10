#include "PlayScene.h"
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "GoalFrag.h"
//#include "FieldTrees.h"
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
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
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

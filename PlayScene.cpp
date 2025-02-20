#include "PlayScene.h"
#include "Field.h"
#include "Player.h"
#include "Item.h"
#include "FieldTrees.h"
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
	Instantiate<Item>(this);
	Instantiate<FieldTrees>(this);
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

#include "PlayScene.h"
#include "Field.h"
#include "Player.h"
#include "Item.h"
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
	Instantiate<Item>(this);
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

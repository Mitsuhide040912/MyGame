#pragma once
#include "Engine/GameObject.h"
class Goblin :
    public GameObject
{
	int hModel_;

	int hModelAnimeGob_[2];
	int animType_;

	float bossSpeed_ = 0.1f;

	float EnemyGobPosX = 10;
	float EnemyGobPosZ = -48;

	float angle = 150.0f;
	float maxDistance = 30.0f;
public:
	Goblin(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};


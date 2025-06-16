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

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


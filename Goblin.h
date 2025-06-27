#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Goblin :
    public GameObject
{
	//struct GoblinUnit
	//{
	//	Transform transform;
	//	Gob_ANM_TYPE animType;
	//	float animFrame;
	//};
	int hModel_;

	int hModelAnimeGob_[2];
	int animType_;

	float bossSpeed_ = 0.1f;

	float EnemyGobPosX = 10;
	float EnemyGobPosZ = -48;

	float angle = 140.0f;
	float maxDistance = 30.0f;

	
	//std::vector<GoblinUnit>Goblins_;



	static int gModelIdle_;
	static int gModelRun_;
public:
	Goblin(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw()override;



	//ŠJ•ú
	void Release() override;

	void SetPosition(const XMFLOAT3& pos);
};


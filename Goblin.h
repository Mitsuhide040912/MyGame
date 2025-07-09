#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Goblin :
    public GameObject
{
	int hModel_;

	int hModelAnimeGob_[2];
	int animType_;
	int isHit_ = 0;

	float bossSpeed_ = 0.1f;

	float EnemyGobPosX = 10;
	float EnemyGobPosZ = -48;

	float angle = 140.0f;
	float maxDistance = 30.0f;

	
	//std::vector<GoblinUnit>Goblins_;



	static int gModelIdle_;
	static int gModelRun_;

	bool rotateClockwise_ = true;
	bool hitFrag_;

	
public:
	Goblin(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw()override;



	//�J��
	void Release() override;

	void SetPosition(const XMFLOAT3& pos);

	void SetRotateDir(bool clockWise);

	void OnCollision(GameObject* pTarget)override;
};


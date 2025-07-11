#pragma once
#include "Engine/GameObject.h"
#include "EnemyAI.h"
#include <DirectXMath.h>
#include <vector>
class Enemy :
	public GameObject
{
	int hModel_;
	int hGobModel_;
	int hModelAnimeBoss_[2];
	int animType_;
	int isHit_ = 0;

	bool hitFrag_;
	bool hModelAnim_;
	bool nextAnimState_;

	float bossSpeed_ = 0.18f;
	float EnemyBossPosX = -11;
	float EnemyBossPosZ = 54;

	float angle = 210.0f;
	float maxDistance = 50.0f;

	EnemyAI em;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Enemy(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void AddPatrolPoint(const DirectX::XMFLOAT3& point);

	void OnCollision(GameObject* pTarget)override;
};


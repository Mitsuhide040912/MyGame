#pragma once
#include "Engine/GameObject.h"
#include "EnemyAI.h"
#include <DirectXMath.h>
#include <vector>
class Enemy :
	public GameObject
{
	int hModel_;
	int hModelAnime_[2];
	int animType_;
	bool hModelAnim_;
	bool nextAnimState_;

	float bossSpeed_ = 0.5f;
	float EnemyPosX = -11;
	//float EnemyPosY = -140;
	float EnemyPosZ = 54;

	//DirectX::XMFLOAT3 enemyForwad{ 0.0f,0.0f,1.0f };
	float angle = 150.0f;
	float maxDistance = 30.0f;

	EnemyAI em;

	float bossRotation = 0.0f;
	float rotationSpeed = XMConvertToRadians(45.0f);
	float maxRotation = XMConvertToRadians(45.0f);
	bool rotateForward = true;
	
	bool bossMove_;
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
};


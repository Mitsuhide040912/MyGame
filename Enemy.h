#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
	int hModel_;

	float EnemyPosX = 105;
	float EnemyPosY = -140;
	float EnemyPosZ = -10;

	DirectX::XMFLOAT3 enemyForwad{ 0.0f,0.0f,1.0f };
	float angle = 90.0f;
	float maxDistance = 10.0f;

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
};


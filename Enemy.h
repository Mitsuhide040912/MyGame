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
	float angle = 210.0f;
	float maxDistance = 50.0f;
	//�{�X�̏�����
	const float ENEMY_INIT_ROT_Y = 90.0f;
	const XMFLOAT3 ENEMY_INIT_SCALE = { 4.0f,4.0f,4.0f };
	const XMFLOAT3 ENEMY_INIT_POS = { -11.0f,0.0f,54.0f };
	//�{�X�̃t���[��
	const int ANIM_STRT_FRAME = 1;
	const int ANIM_END_SPEED = 1;
	const int ANIM_Idle_FRAME = 242;
	const int ANIM_Walk_FRAME = 86;
	//Maya�ō�������f���̊p�x���኱����Ă��邽��
	const float mayaCorection = 5.0f;

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


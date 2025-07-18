#include "Enemy.h"
#include "Field.h"
#include "Player.h"
#include "Bullet.h"
#include <DirectXMath.h>
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "EnemyAI.h"
#include "Engine/time.h"
#include <cmath>
using namespace DirectX;

enum ANM_TYPE
{
	WAIT = 0,
	Walk,
	MAX
};

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy")
	, hModel_(-1)
	, hModelAnimeBoss_(-1),hitFrag_(false)
{
}

void Enemy::Initialize()
{
	hModelAnimeBoss_[0] = Model::Load("Model\\BossIdle.fbx");//���ҋ@
	assert(hModelAnimeBoss_[0] >= 0);
	hModelAnimeBoss_[1] = Model::Load("Model\\BossWalking.fbx");//������
	assert(hModelAnimeBoss_[1] >= 0);
	
	transform_.rotate_.y = ENEMY_INIT_ROT_Y;
	transform_.position_ = ENEMY_INIT_POS;

	transform_.scale_ = ENEMY_INIT_SCALE;

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 7, 0), XMFLOAT3(10, 7, 10));
	AddCollider(collision);
	//���ҋ@���[�V����
	Model::SetAnimFrame(hModelAnimeBoss_[0], ANIM_STRT_FRAME, ANIM_Idle_FRAME, ANIM_END_SPEED);

}

void Enemy::Update()
{
	switch (animType_)
	{
	case ANM_TYPE::WAIT:
		hModel_ = hModelAnimeBoss_[0];
		break;
	case ANM_TYPE::Walk:
		hModel_ = hModelAnimeBoss_[1];
		break;
	default:
		break;
	}



	XMMATRIX world = transform_.GetWorldMatrix();
	XMVECTOR forwardVec = XMVector3Normalize(world.r[2]);
	XMFLOAT3 enemyForward;
	XMStoreFloat3(&enemyForward, forwardVec);
	// �v���C���[�̈ʒu���擾
	Player* pPlayer = (Player*)FindObject("Player");  // �v���C���[�I�u�W�F�N�g���擾
	if (!pPlayer) return;  // �v���C���[��������Ȃ��ꍇ�͉������Ȃ�

	XMFLOAT3 playerPos = pPlayer->GetPosition();  // �v���C���[�̈ʒu���擾
	//XMFLOAT3 enemyPos = transform_.position_;  // �G�l�~�[�̈ʒu���擾

	Field* pField = (Field*)FindObject("Field");
	int hFieldModel = pField->GetModelHandle();
	RayCastData data;
	data.start = transform_.position_;
	data.start.y += 4;
	data.dir = XMFLOAT3({ 0,-1,0 });
	Model::RayCast(hFieldModel, &data);

	if (data.hit)
	{
		transform_.position_.y -= data.dist - 4;
	}


	bool isPlayerInRangeBoss = EnemyAI::IsEnemyTarget(transform_.position_, enemyForward, playerPos, angle, maxDistance);
	if (isPlayerInRangeBoss) {
		if (animType_ != ANM_TYPE::Walk) {
			animType_ = ANM_TYPE::Walk;
			Model::SetAnimFrame(hModelAnimeBoss_[1], ANIM_STRT_FRAME, ANIM_Walk_FRAME, ANIM_END_SPEED);
		}
		XMVECTOR enemyPosVec = XMLoadFloat3(&transform_.position_);
		XMVECTOR playerPosVec = XMLoadFloat3(&playerPos);
		// �����x�N�g���iXZ�j
		XMVECTOR dirVec = XMVectorSubtract(playerPosVec, enemyPosVec);
		dirVec = XMVector3Normalize(dirVec);
		// atan2 �� ���W�A�� �� �x���֕ϊ�
		XMFLOAT3 dirFlat;
		XMStoreFloat3(&dirFlat, dirVec);
		float angle = atan2f(dirFlat.x, dirFlat.z);
		float degree = XMConvertToDegrees(angle);
		// Maya�␳
		transform_.rotate_.y = degree - 5.0f;
		// �ړ�
		XMVECTOR move = XMVectorScale(dirVec, bossSpeed_);
		enemyPosVec = XMVectorAdd(enemyPosVec, move);
		XMStoreFloat3(&transform_.position_, enemyPosVec);
	}
	else
	{
		if (animType_ != ANM_TYPE::WAIT) {
			animType_ = ANM_TYPE::WAIT;
			Model::SetAnimFrame(hModelAnimeBoss_[0], ANIM_STRT_FRAME, ANIM_Idle_FRAME, ANIM_END_SPEED);
		}
	}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::AddPatrolPoint(const DirectX::XMFLOAT3& point)
{
	em.AddPatrolPoint(point);
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet") {
		hitFrag_ = true;
		isHit_++;

		if (isHit_ >= 3) {
			
			KillMe();
		}
	}
	else
	{
		hitFrag_ = false;
	}
}


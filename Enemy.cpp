#include "Enemy.h"
#include "Field.h"
#include "Player.h"
#include <DirectXMath.h>
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

#include "EnemyAI.h"
#include <cmath>
using namespace DirectX;

enum ANM_TYPE
{
	WAIT = 0,
	Walk,
};



Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	//hModel_ = Model::Load("Model\\box.fbx");
	hModelAnime_[0] = Model::Load("Model\\Boss Idle.fbx");
	//assert(hModel_ >= 0);

	transform_.position_ = { EnemyPosX,EnemyPosY,EnemyPosZ };
	transform_.scale_ = { 3,3,3 };

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(4, 4, 4));
	AddCollider(collision);
	//�ҋ@
	Model::SetAnimFrame(hModelAnime_[0], 1, 242, 1);
}

void Enemy::patrolUpdate(float deltaTime)
{
	patrolUpdate(deltaTime);
	switch (animType_)
	{
	case ANM_TYPE::WAIT:
		hModel_ = hModelAnime_[0];
		break;
	default:
		break;
	}

	XMMATRIX world = transform_.GetWorldMatrix();
	XMVECTOR forwardVec = XMVector3Normalize(world.r[2]);
	XMFLOAT3 enemyForward;
	XMStoreFloat3(&enemyForward, forwardVec)
		;
	//// �v���C���[�̈ʒu���擾
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

	if (EnemyAI::IsEnemyTarget(transform_.position_, enemyForward, playerPos, angle, maxDistance))
	{
		XMVECTOR enemyPos = XMLoadFloat3(&transform_.position_);
		XMVECTOR playerPosVec = XMLoadFloat3(&playerPos);

		XMVECTOR direction = XMVector3Normalize(XMVectorSubtract(playerPosVec, enemyPos));
		XMVECTOR move = XMVectorScale(direction, bossSpeed_);
		enemyPos = XMVectorAdd(enemyPos, move);
		XMStoreFloat3(&transform_.position_, enemyPos);


		//	//// �v���C���[�ƃG�l�~�[�̋������v�Z
		//	float dx = playerPos.x - enemyPos.x;
		//	float dy = playerPos.y - enemyPos.y;
		//	float dz = playerPos.z - enemyPos.z;
		//	float distance = sqrt(dx * dx + dy * dy + dz * dz);

		//	// �v���C���[�����a3���[�g���ȓ��ɂ���ꍇ�A�ǔ�����
		//	if (distance <= 20.0f)
		//	{
		//		// �ǔ��������v�Z
		//		XMVECTOR dir = XMVectorSet(dx, dy, dz, 0);  // �v���C���[�����x�N�g��
		//		dir = XMVector3Normalize(dir);  // ���K�����ĒP�ʃx�N�g���ɂ���

		//		// 1�t���[���������i��
		//		float speed = 0.15f;  // 1�t���[�����̐i�s�����i�����\�j
		//		XMVECTOR move = dir * speed;  // �ړ��ʂ��v�Z

		//		// �G�l�~�[�̈ʒu���X�V
		//		XMVECTOR newPos = XMLoadFloat3(&enemyPos) + move;
		//		XMStoreFloat3(&transform_.position_, newPos);  // �V�����ʒu���Z�b�g
		//	}
		//}
	}
}

void Enemy::Update()
{
	
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


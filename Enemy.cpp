#include "Enemy.h"
#include "Field.h"
#include "Player.h"
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

enum Gob_ANM_TYPE
{
	GobWAIT = 0,
	GobWalk,
	GobMAX
};

Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1), hModelAnimeBoss_(-1), hModelAnimeGob_(-1),bossMove_(false)
{
}

void Enemy::Initialize()
{
	hModelAnimeBoss_[0] = Model::Load("Model\\BossIdle.fbx");//←待機
	assert(hModelAnimeBoss_[0] >= 0);
	hModelAnimeBoss_[1] = Model::Load("Model\\BossWalking.fbx");//←歩く
	assert(hModelAnimeBoss_[1] >= 0);

	hModelAnimeGob_[0] = Model::Load("Model\\GoblinIdle.fbx");//←待機
	assert(hModelAnimeGob_[0] >= 0);
	hModelAnimeGob_[1] = Model::Load("Model\\GoblinRun.fbx");//←歩く
	assert(hModelAnimeGob_[1] >= 0);
	
	transform_.rotate_.y = 180;
	transform_.position_ = { EnemyBossPosX,0,EnemyBossPosZ };

	transform_.scale_ = { 2.5,2.5,2.5 };
	Gobtrs.position_ = { EnemyGobPosX ,0,EnemyGobPosZ };

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(4, 4, 4));
	AddCollider(collision);

	animType_ = ANM_TYPE::WAIT;
	hModel_ = hModelAnimeBoss_[0];
	Model::SetAnimFrame(hModel_, 1, 242, 1);

	animType_ = Gob_ANM_TYPE::GobWAIT;
	hGobModel_ = hModelAnimeGob_[0];
	Model::SetAnimFrame(hGobModel_, 1, 183, 1);

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

	switch (animType_)
	{
	case Gob_ANM_TYPE::GobWAIT:
		hGobModel_ = hModelAnimeGob_[0];
		break;
	case Gob_ANM_TYPE::GobWalk:
		hGobModel_ = hModelAnimeGob_[1];
		break;
	default:
		break;
	}

	XMMATRIX world = transform_.GetWorldMatrix();
	XMVECTOR forwardVec = XMVector3Normalize(world.r[2]);
	XMFLOAT3 enemyForward;
	XMStoreFloat3(&enemyForward, forwardVec)
		;
	//// プレイヤーの位置を取得
	Player* pPlayer = (Player*)FindObject("Player");  // プレイヤーオブジェクトを取得
	if (!pPlayer) return;  // プレイヤーが見つからない場合は何もしない

	XMFLOAT3 playerPos = pPlayer->GetPosition();  // プレイヤーの位置を取得
	//XMFLOAT3 enemyPos = transform_.position_;  // エネミーの位置を取得

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
			Model::SetAnimFrame(hModelAnimeBoss_[1], 1, 86, 1);
		}
		XMVECTOR enemyPos = XMLoadFloat3(&transform_.position_);//↓敵の索敵
		XMVECTOR playerPosVec = XMLoadFloat3(&playerPos);

		XMVECTOR direction = XMVector3Normalize(XMVectorSubtract(playerPosVec, enemyPos));
		XMVECTOR move = XMVectorScale(direction, bossSpeed_);
		enemyPos = XMVectorAdd(enemyPos, move);
		XMStoreFloat3(&transform_.position_, enemyPos);//↑
	}
	else
	{
		if (animType_ != ANM_TYPE::WAIT) {
			animType_ = ANM_TYPE::WAIT;
			Model::SetAnimFrame(hModelAnimeBoss_[0], 1, 242, 1);
		}
	}

	bool isPlayerInRangeGoblin = EnemyAI::IsEnemyTarget(transform_.position_, enemyForward, playerPos, angle, maxDistance);
	if (isPlayerInRangeGoblin) {
		if (animType_ != Gob_ANM_TYPE::GobWAIT) {
			animType_ = Gob_ANM_TYPE::GobWAIT;
			Model::SetAnimFrame(hModelAnimeGob_[1], 1, 24, 1);
		}

		XMVECTOR enemyPos = XMLoadFloat3(&transform_.position_);//↓敵の索敵
		XMVECTOR playerPosVec = XMLoadFloat3(&playerPos);

		XMVECTOR direction = XMVector3Normalize(XMVectorSubtract(playerPosVec, enemyPos));
		XMVECTOR move = XMVectorScale(direction, bossSpeed_);
		enemyPos = XMVectorAdd(enemyPos, move);
		XMStoreFloat3(&transform_.position_, enemyPos);//↑
	}
	else
	{
		if (animType_ != Gob_ANM_TYPE::GobWAIT) {
			animType_ = Gob_ANM_TYPE::GobWAIT;
			Model::SetAnimFrame(hModelAnimeGob_[0], 1, 183, 1);
		}
	}


	//if (EnemyAI::IsEnemyTarget(transform_.position_, enemyForward, playerPos, angle, maxDistance))
	//{
	//	XMVECTOR enemyPos = XMLoadFloat3(&transform_.position_);
	//	XMVECTOR playerPosVec = XMLoadFloat3(&playerPos);

	//	XMVECTOR direction = XMVector3Normalize(XMVectorSubtract(playerPosVec, enemyPos));
	//	XMVECTOR move = XMVectorScale(direction, bossSpeed_);
	//	enemyPos = XMVectorAdd(enemyPos, move);
	//	XMStoreFloat3(&transform_.position_, enemyPos);
	//}

	//if (rotateForward)
	//{
	//	bossRotation += rotationSpeed * Time::DeltaTime();
	//	if (bossRotation >= maxRotation)
	//	{
	//		bossRotation = maxRotation;
	//		rotateForward = false;
	//	}
	//}
	//else
	//{
	//	bossRotation -= rotationSpeed * Time::DeltaTime();
	//	if (bossRotation <= 0.0f)
	//	{
	//		bossRotation = 0.0f;
	//		rotateForward = true;
	//	}
	//}
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Model::SetTransform(hGobModel_, Gobtrs);
	Model::Draw(hGobModel_);
}

void Enemy::Release()
{
}

void Enemy::AddPatrolPoint(const DirectX::XMFLOAT3& point)
{
	em.AddPatrolPoint(point);
}


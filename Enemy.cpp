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



Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1),hModelAnime_(-1),bossMove_(false)
{
}

void Enemy::Initialize()
{
	//hModel_ = Model::Load("Model\\box.fbx");
	hModelAnime_[0] = Model::Load("Model\\BossIdle.fbx");
	assert(hModelAnime_[0] >= 0);
	//hModelAnime_[1] = Model::Load("Model\\BossWalking.fbx");
	//assert(hModelAnime_[1] >= 0);
	transform_.rotate_.y = 180;
	transform_.position_ = { EnemyPosX,0,EnemyPosZ };
	transform_.scale_ = { 2.5,2.5,2.5 };

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(4, 4, 4));
	AddCollider(collision);
	//待機
	Model::SetAnimFrame(hModelAnime_[0], 1, 242, 1);
}

void Enemy::Update()
{
	//patrolUpdate(deltaTime);
	switch (animType_)
	{
	case ANM_TYPE::WAIT:
		hModel_ = hModelAnime_[0];
		break;
	case ANM_TYPE::Walk:
		hModel_ = hModelAnime_[1];
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



	if (EnemyAI::IsEnemyTarget(transform_.position_, enemyForward, playerPos, angle, maxDistance))
	{
		//if (bossMove_)
		//{
		//	animType_ = ANM_TYPE::Walk;
		//}

		XMVECTOR enemyPos = XMLoadFloat3(&transform_.position_);
		XMVECTOR playerPosVec = XMLoadFloat3(&playerPos);

		XMVECTOR direction = XMVector3Normalize(XMVectorSubtract(playerPosVec, enemyPos));
		XMVECTOR move = XMVectorScale(direction, bossSpeed_);
		enemyPos = XMVectorAdd(enemyPos, move);
		XMStoreFloat3(&transform_.position_, enemyPos);

		//bossMove_ = true;
	}

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
}

void Enemy::Release()
{
}

void Enemy::AddPatrolPoint(const DirectX::XMFLOAT3& point)
{
	em.AddPatrolPoint(point);
}


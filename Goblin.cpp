#include "Goblin.h"
#include "Field.h"
#include "Engine/Model.h"

#include "Player.h"
#include <DirectXMath.h>
#include "Engine/BoxCollider.h"

#include "EnemyAI.h"
#include <cmath>
#include"Engine/Debug.h"

using namespace DirectX;

enum Gob_ANM_TYPE
{
	GobWAIT = 0,
	GobWalk,
	GobMAX
};

Goblin::Goblin(GameObject* parent)
	:GameObject(parent, "Goblin"),hModel_(-1),hModelAnimeGob_(-1)
{
}

void Goblin::Initialize()
{
	hModelAnimeGob_[0] = Model::Load("Model\\GoblinIdle.fbx");//←待機
	assert(hModelAnimeGob_[0] >= 0);
	hModelAnimeGob_[1] = Model::Load("Model\\GoblinRun.fbx");//←歩く
	assert(hModelAnimeGob_[1] >= 0);
	transform_.position_ = { EnemyGobPosX ,0,EnemyGobPosZ };
	transform_.rotate_.y = 90.0;
	transform_.scale_ = { 2.5,2.5,2.5 };

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(4, 4, 4));
	AddCollider(collision);

	animType_ = Gob_ANM_TYPE::GobWAIT;
	hModel_ = hModelAnimeGob_[0];
	Model::SetAnimFrame(hModel_, 1, 183, 1);
}

void Goblin::Update()
{
	transform_.rotate_.y += 1.0f;
	switch (animType_)
	{
	case Gob_ANM_TYPE::GobWAIT:
		hModel_ = hModelAnimeGob_[0];
		break;
	case Gob_ANM_TYPE::GobWalk:
		hModel_ = hModelAnimeGob_[1];
		break;
	default:
		break;
	}
	// プレイヤーの位置を取得
	Player* pPlayer = (Player*)FindObject("Player");  // プレイヤーオブジェクトを取得
	if (!pPlayer) return;  // プレイヤーが見つからない場合は何もしない
	XMFLOAT3 playerPos = pPlayer->GetPosition();  // プレイヤーの位置を取得
	XMMATRIX world = transform_.GetWorldMatrix();
	XMVECTOR forwardVec = XMVector3Normalize(world.r[2]);
	XMFLOAT3 enemyForward;
	XMStoreFloat3(&enemyForward, forwardVec);

	bool isPlayerInRangeGoblin = EnemyAI::IsEnemyTarget(transform_.position_, enemyForward, playerPos, angle, maxDistance);
	if (isPlayerInRangeGoblin) {
		if (animType_ != Gob_ANM_TYPE::GobWalk) {
			animType_ = Gob_ANM_TYPE::GobWalk;
			Model::SetAnimFrame(hModelAnimeGob_[1], 1, 48, 1);
		}
		XMVECTOR enemyPosVec = XMLoadFloat3(&transform_.position_);
		XMVECTOR playerPosVec = XMLoadFloat3(&playerPos);
		// 方向ベクトル（XZ）
		XMVECTOR dirVec = XMVectorSubtract(playerPosVec, enemyPosVec);
		dirVec = XMVector3Normalize(dirVec);
		// atan2 → ラジアン → 度数へ変換
		XMFLOAT3 dirFlat;
		XMStoreFloat3(&dirFlat, dirVec);
		float angle = atan2f(dirFlat.x, dirFlat.z);
		float degree = XMConvertToDegrees(angle);
		// Maya補正
		transform_.rotate_.y = degree - 5.0f;
		// 移動
		XMVECTOR move = XMVectorScale(dirVec, bossSpeed_);
		enemyPosVec = XMVectorAdd(enemyPosVec, move);
		XMStoreFloat3(&transform_.position_, enemyPosVec);
	}
	else
	{
		if (animType_ != Gob_ANM_TYPE::GobWAIT) {
			animType_ = Gob_ANM_TYPE::GobWAIT;
			Model::SetAnimFrame(hModelAnimeGob_[0], 1, 183, 1);
		}
	}
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
}



void Goblin::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

void Goblin::Release()
{
}

void Goblin::SetPosition(const XMFLOAT3& pos)
{
}

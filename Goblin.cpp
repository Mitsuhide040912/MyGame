#include "Goblin.h"
#include "Field.h"
#include "Bullet.h"
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
	:GameObject(parent, "Goblin")
	,hModel_(-1),hModelAnimeGob_(-1),hitFrag_(false)
{
}

void Goblin::Initialize()
{
	hModelAnimeGob_[0] = Model::Load("Model\\GoblinIdle.fbx");//←待機
	assert(hModelAnimeGob_[0] >= 0);
	hModelAnimeGob_[1] = Model::Load("Model\\GoblinRun.fbx");//←歩く
	assert(hModelAnimeGob_[1] >= 0);
	//transform_.position_ = { EnemyGobPosX ,0,EnemyGobPosZ };
	transform_.scale_ = GOB_INIT_SCALE;

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 2, 0), XMFLOAT3(3, 5, 3));
	AddCollider(collision);

	Model::SetAnimFrame(hModelAnimeGob_[0], ANIM_STRT_FRAME, ANIM_Idle_FRAME, ANIM_END_SPEED);
}

void Goblin::Update()
{
	//↓ゴブリンを左右両方回転させる
	transform_.rotate_.y += rotateClockwise_ ? 1.0f : -1.0f;
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
			Model::SetAnimFrame(hModelAnimeGob_[1], ANIM_STRT_FRAME, ANIM_Walk_FRAME, ANIM_END_SPEED);
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
		transform_.rotate_.y = degree - mayaCorection;
		// 移動
		XMVECTOR move = XMVectorScale(dirVec, gobSpeed_);
		enemyPosVec = XMVectorAdd(enemyPosVec, move);
		XMStoreFloat3(&transform_.position_, enemyPosVec);
	}
	else
	{
		if (animType_ != Gob_ANM_TYPE::GobWAIT) {
			animType_ = Gob_ANM_TYPE::GobWAIT;
			Model::SetAnimFrame(hModelAnimeGob_[0], ANIM_STRT_FRAME, ANIM_Idle_FRAME, ANIM_END_SPEED);
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


	//↓yが-157を超えた時点でゴブリン死滅
	if (transform_.position_.y < GOBLIN_DETH_HEIGHT) {
		KillMe();
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

void Goblin::SetRotateDir(bool clockWise)
{
	rotateClockwise_ = clockWise;
}

void Goblin::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet") {
		hitFrag_ = true;
		isHit_++;

		if (isHit_ >= 2) {
			KillMe();
		}
	}
	else
	{
		hitFrag_ = false;
	}
}

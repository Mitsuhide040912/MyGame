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
	GobWALK,
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
	switch (animType_)
	{
	case Gob_ANM_TYPE::GobWAIT:
		hModel_ = hModelAnimeGob_[0];
		break;
	case Gob_ANM_TYPE::GobWALK:
		hModel_ = hModelAnimeGob_[1];
		break;
	default:
		break;
	}
	// プレイヤーの位置を取得
	Player* pPlayer = (Player*)FindObject("Player");  // プレイヤーオブジェクトを取得
	if (!pPlayer) return;  // プレイヤーが見つからない場合は何もしない
	XMFLOAT3 playerPos = pPlayer->GetPosition();  // プレイヤーの位置を取得

	float distance = XMVectorGetX(XMVector3Length(XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&playerPos)));
	XMFLOAT3 forward = { sinf(XMConvertToRadians(transform_.rotate_.y)),0.0f,cosf(XMConvertToRadians(transform_.rotate_.y)) };
	XMVECTOR enemyForward = XMVector3Normalize(XMLoadFloat3(&forward));
	XMVECTOR toPlayer = XMVector3Normalize(XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_));
	float dot = XMVectorGetX(XMVector3Dot(enemyForward, toPlayer));
	dot = (dot < -1.0f) ? -1.0f : (dot > 1.0f ? 1.0f : dot);
	float angleToPlayer = acosf(dot);

	const float VIEN_ANGLE = XMConvertToRadians(100.0f);

	if (distance < CHASE_RANGE && angleToPlayer < VIEN_ANGLE / 2) {
		
		chasing_ = true;
	}
	if (chasing_&&!returning_){
		if (animType_ != Gob_ANM_TYPE::GobWALK) {
			animType_ = Gob_ANM_TYPE::GobWALK;
			Model::SetAnimFrame(hModelAnimeGob_[1], ANIM_STRT_FRAME, ANIM_Walk_FRAME, ANIM_END_SPEED);
		}
		XMVECTOR dirVec = XMVector3Normalize(XMLoadFloat3(&playerPos) - XMLoadFloat3(&transform_.position_));
		transform_.rotate_.y = XMConvertToDegrees(atan2f(XMVectorGetX(dirVec), XMVectorGetZ(dirVec))) - mayaCorection;
		XMVECTOR move = XMVectorScale(dirVec, gobSpeed_);
		XMStoreFloat3(&transform_.position_, XMVectorAdd(XMLoadFloat3(&transform_.position_), move));

		if (distance >= LOST_RANGE) {
			returning_ = true;
		}
	}
	if (returning_&&chasing_) {
		if (animType_ != Gob_ANM_TYPE::GobWALK) {
			animType_ = Gob_ANM_TYPE::GobWALK;
			Model::SetAnimFrame(hModelAnimeGob_[1], ANIM_STRT_FRAME, ANIM_Walk_FRAME, ANIM_END_SPEED);
		}
		XMVECTOR enemyPosVec = XMLoadFloat3(&transform_.position_);
		XMVECTOR homePosVec = XMLoadFloat3(&initPos_);
		XMVECTOR dirVec = XMVector3Normalize(XMVectorSubtract(homePosVec, enemyPosVec));
		transform_.rotate_.y = XMConvertToDegrees(atan2f(XMVectorGetX(dirVec), XMVectorGetZ(dirVec))) - mayaCorection;
		XMVECTOR move = XMVectorScale(dirVec, gobReturnSpeed_);
		XMStoreFloat3(&transform_.position_, XMVectorAdd(enemyPosVec, move));
		float homeDist = XMVectorGetX(XMVector3Length(XMLoadFloat3(&transform_.position_) - XMLoadFloat3(&initPos_)));
		if (homeDist < 1.0f) {
			returning_ = false;
			chasing_ = false;
			if (animType_ != Gob_ANM_TYPE::GobWAIT) {
				animType_ = Gob_ANM_TYPE::GobWAIT;
				Model::SetAnimFrame(hModelAnimeGob_[0], ANIM_STRT_FRAME, ANIM_Idle_FRAME, ANIM_END_SPEED);
			}

		}
	}
	Field* pField = (Field*)FindObject("Field");
	int hFieldModel = pField->GetModelHandle();
	RayCastData data;
	data.start = transform_.position_;
	data.start.y += 4;
	data.dir = XMFLOAT3({ 0,-1,0 });
	Model::RayCast(hFieldModel, &data);
	initPos_.y = transform_.position_.y;

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
	transform_.position_ = pos;
	initPos_ = pos;
	
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

#include "Enemy.h"
#include "Field.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),hModel_(-1)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Model\\box.fbx");
	assert(hModel_ > 0);
	
	transform_.position_ = { EnemyPosX,EnemyPosY,EnemyPosZ };
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(4, 4, 4));
	AddCollider(collision);
}

void Enemy::Update()
{

	

	// プレイヤーの位置を取得
	//↓GPT案
	Player* pPlayer = (Player*)FindObject("Player");  // プレイヤーオブジェクトを取得
	if (!pPlayer) return;  // プレイヤーが見つからない場合は何もしない

	XMFLOAT3 playerPos = pPlayer->GetPosition();  // プレイヤーの位置を取得
	XMFLOAT3 enemyPos = transform_.position_;  // エネミーの位置を取得

	// プレイヤーとエネミーの距離を計算
	float dx = playerPos.x - enemyPos.x;
	float dy = playerPos.y - enemyPos.y;
	float dz = playerPos.z - enemyPos.z;
	float distance = sqrt(dx * dx + dy * dy + dz * dz);

	// プレイヤーが半径3メートル以内にいる場合、追尾する
	if (distance <= 20.0f)
	{
		// 追尾方向を計算
		XMVECTOR dir = XMVectorSet(dx, dy, dz, 0);  // プレイヤー方向ベクトル
		dir = XMVector3Normalize(dir);  // 正規化して単位ベクトルにする

		// 1フレーム分だけ進む
		float speed = 0.15f;  // 1フレーム分の進行距離（調整可能）
		XMVECTOR move = dir * speed;  // 移動量を計算

		// エネミーの位置を更新
		XMVECTOR newPos = XMLoadFloat3(&enemyPos) + move;
		XMStoreFloat3(&transform_.position_, newPos);  // 新しい位置をセット
	}
	//float dir = 0;
	//if (transform_.position_.x + 5)
	//{
	//	transform_.position_.x - 5;
	//}
	//transform_.position_.z = 60.0f;
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

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

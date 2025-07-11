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
	float EnemyBossPosX = -11;
	float EnemyBossPosZ = 54;

	float angle = 210.0f;
	float maxDistance = 50.0f;

	EnemyAI em;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void AddPatrolPoint(const DirectX::XMFLOAT3& point);

	void OnCollision(GameObject* pTarget)override;
};


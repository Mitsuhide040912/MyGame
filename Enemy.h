#pragma once
#include "Engine/GameObject.h"
#include "EnemyAI.h"
#include <DirectXMath.h>
#include <vector>
class Enemy :
	public GameObject
{
	int hModel_;
	int hModelAnime_[2];
	int animType_;
	bool hModelAnim_;
	bool nextAnimState_;

	float bossSpeed_ = 0.5f;
	float EnemyPosX = -11;
	//float EnemyPosY = -140;
	float EnemyPosZ = 54;

	//DirectX::XMFLOAT3 enemyForwad{ 0.0f,0.0f,1.0f };
	float angle = 150.0f;
	float maxDistance = 30.0f;

	EnemyAI em;

	float bossRotation = 0.0f;
	float rotationSpeed = XMConvertToRadians(45.0f);
	float maxRotation = XMConvertToRadians(45.0f);
	bool rotateForward = true;
	
	bool bossMove_;
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
};


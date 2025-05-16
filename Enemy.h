#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
	int hModel_;

	float EnemyPosX = 105;
	float EnemyPosY = -140;
	float EnemyPosZ = -10;

	DirectX::XMFLOAT3 enemyForwad{ 0.0f,0.0f,1.0f };
	float angle = 90.0f;
	float maxDistance = 10.0f;

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
};


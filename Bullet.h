#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>
class Bullet :
    public GameObject
{
	int hModel_;
	int isHit = 0;
	DirectX::XMVECTOR velocity_;
	float gravity_;
	const float BULLET_DETH_HEIGHT = -140.0f;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Bullet(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	
	void SetVelocity(const DirectX::XMFLOAT3& dir, float speed, float angreDigrees);
	void OnCollision(GameObject* pTarget)override;
};


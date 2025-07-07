#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>
class Bullet :
    public GameObject
{
	int hModel_;
	DirectX::XMVECTOR velocity_;
	float gravity_;
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
};


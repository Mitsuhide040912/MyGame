#pragma once
#include "Engine/GameObject.h"
class Block :
    public GameObject
{
	int hModel_;
	float x, y, z;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Block(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* pTarget)override;
};


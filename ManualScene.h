#pragma once
#include "Engine/GameObject.h"
class ManualScene :
    public GameObject
{
	int hImege_;
	int select_;//選択
	int prevUpKey_;//前フレームの上キー
	int prevDownKey_;//前フレームの下キー

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ManualScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};


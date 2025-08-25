#pragma once
#include "Engine/GameObject.h"
class TitleScene :
    public GameObject
{
	int hImege_;
	int select_;//選択
	int prevUpKey_;//前フレームの上キー
	int prevDownKey_;//前フレームの下キー
	int hSound_;//サウンド番号

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};


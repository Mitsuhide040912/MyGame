#pragma once
#include "Engine/GameObject.h"
class Timer :
    public GameObject
{
	float timer_;//←制限時間
	bool isTimeUp_;//←時間切れかどうか判断
	int hImage_;
	float x, y, z;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Timer(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void DrawDigit(int digit, float posX, float posY);
};


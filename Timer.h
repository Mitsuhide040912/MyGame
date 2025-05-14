#pragma once
#include "Engine/GameObject.h"
class Timer :
    public GameObject
{
	const float IMAGE_WIDTH = 51.2;
	int timer_;//←制限時間
	bool isTimeUp_;//←時間切れかどうか判断
	int hImage_;
	float x, y, z;

	int tenMin_;
	int min_;
	int tenSec_;
	int sec_;

	float oneSec_;

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
};


#pragma once
#include "Engine/GameObject.h"
class Timer :
    public GameObject
{

	int timer_;//←制限時間
	int hImage_;
	int tenMin_;
	int min_;
	int tenSec_;
	int sec_;
	int cutOutRangeY = 30;
	int cutOutRangewidth = 50;
	int cutOutRangeheight = 90;

	float oneSec_;

	bool isTimeUp_;//←時間切れかどうか判断

	const float IMAGE_WIDTH = 51.2;
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


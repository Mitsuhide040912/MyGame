#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Goblin :
    public GameObject
{
	int hModel_;
	int hModelAnimeGob_[2];
	int animType_;
	//何回当たっているか
	int isHit_ = 0;
	//ゴブリンがプレイヤーを追いかけたりするときの速度
	float gobSpeed_ = 0.10f;
	//ゴブリンが初期位置に戻るときの速度
	float gobReturnSpeed_ = 0.40f;

	float patrolTimer_ = 0.0f;
	float fallTime_;
	float prevDist_;
	float fallDist_;

	bool hitFrag_;
	bool returning_ = false;//戻るフラグ
	bool chasing_ = false;
	bool thisFall_;

	//ゴブリンの初期化
	const XMFLOAT3 GOB_INIT_SCALE = { 2.5f,2.5f,2.5f };
	//ゴブリンのフレーム
	const int ANIM_STRT_FRAME = 1;
	const int ANIM_END_SPEED = 1;
	const int ANIM_Idle_FRAME = 183;
	const int ANIM_Walk_FRAME = 48;

	//ランダム係数
	const int RAND_FACTOR = 100;

	//レイの位置
	const float RAY_START_HEIGHT = 4.0f;


	const float CHASE_RANGE = 40.0f;//追跡開始距離
	const float LOST_RANGE = 50.0f; //視野外

	const float VIEN_ANGLE = XMConvertToRadians(100.0f);//ゴブリンの視野角（度→ラジアン）

	//徘徊用定数
	const float PATROL_UPDATE_DT = 0.016f;
	const float PATROL_MIN_TIME = 0.5f;
	const float PATROL_MAX_TIME = 1.0f;
	const float PATROL_SPEED_RATE = 0.6f;
	const float PATROL_ANGLE_RANGE = 360.0f;

	const float CHECK_FORWARD_DIST = 3.0f;
	const float MAX_FLOOR_HEIGHT_DIST = 10.0f;

	const float GOB_FALL_SPEED = 15.0f;

	//ゴブリンが一定のyの値を超えていたら削除
	const float GOBLIN_DETH_HEIGHT = -150.0f;
	//Mayaで作ったモデルの角度が若干ずれているため
	const float mayaCorection = 5.0f;

	//落下速度
	const float FALL_SPEED = 15.0f;

	XMFLOAT3 initPos_;//初期位置

	XMFLOAT3 patrolDir_{ 0,0,0 };
public:
	Goblin(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw()override;
	
	//開放
	void Release() override;

	void SetPosition(const XMFLOAT3& pos);

	void OnCollision(GameObject* pTarget)override;

	void Fall();
};


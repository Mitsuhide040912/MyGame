#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Goblin :
    public GameObject
{
	int hModel_;
	int hModelAnimeGob_[2];
	int animType_;
	int isHit_ = 0;

	float gobSpeed_ = 0.10f;
	float gobReturnSpeed_ = 0.40f;
	float angle = 160.0f;
	float maxDistance = 30.0f;

	//bool rotateClockwise_ = true;
	bool hitFrag_;
	bool returning_ = false;//戻るフラグ
	bool chasing_ = false;

	//ゴブリンの初期化
	const XMFLOAT3 GOB_INIT_SCALE = { 2.5f,2.5f,2.5f };
	//ゴブリンのフレーム
	const int ANIM_STRT_FRAME = 1;
	const int ANIM_END_SPEED = 1;
	const int ANIM_Idle_FRAME = 183;
	const int ANIM_Walk_FRAME = 48;
	const float CHASE_RANGE = 40.0f;//追跡開始距離
	const float LOST_RANGE = 50.0f; //視野外

	//Gob_ANM_TYPE prevAnimType_ = GobWAIT;

	//ゴブリンが一定のyの値を超えていたら削除
	const float GOBLIN_DETH_HEIGHT = -150.0f;
	//Mayaで作ったモデルの角度が若干ずれているため
	const float mayaCorection = 5.0f;

	XMFLOAT3 initPos_;//初期位置
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
};


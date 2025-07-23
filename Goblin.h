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

	float gobSpeed_ = 0.16f;
	float angle = 160.0f;
	float maxDistance = 30.0f;

	bool rotateClockwise_ = true;
	bool hitFrag_;

	//ゴブリンの初期化
	const XMFLOAT3 GOB_INIT_SCALE = { 2.5f,2.5f,2.5f };
	//ゴブリンのフレーム
	const int ANIM_STRT_FRAME = 1;
	const int ANIM_END_SPEED = 1;
	const int ANIM_Idle_FRAME = 183;
	const int ANIM_Walk_FRAME = 48;
	//ゴブリンが一定のyの値を超えていたら削除
	const float GOBLIN_DETH_HEIGHT = -150.0f;
	//Mayaで作ったモデルの角度が若干ずれているため
	const float mayaCorection = 5.0f;

	
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

	void SetRotateDir(bool clockWise);

	void OnCollision(GameObject* pTarget)override;
};


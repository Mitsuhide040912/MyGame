#pragma once
#include "Engine/GameObject.h"
class Player :
    public GameObject
{
    int hModel_;
    int hModelanime_[3];
    int fall_;
    bool hModelanim_;
    bool nextAnimState_;
    float prevDist_;
    float fallDist_;
    bool thisFall_;
    float fallTime;
    XMVECTOR front_;
    float speed_;
    int camState_;//カメラタイプの指定
    int animType_;//アニメーションのタイプの指定
    XMFLOAT3 f;
    XMVECTOR v = XMLoadFloat3(&f);
    bool isItem_;
    const int ANIM_STRT_FRAME = 1;
    const int ANIM_END_SPEED = 1;
    const int ANIM_Idle_FRAME = 65;
    const int ANMI_Running_FRAME = 50;
    const int ANIM_Pickup_FRAME = 50;

    float gravity = 0.0f;//初期の重力
    float velocityY = 0.0f;//初期速度
    float MaxGravity = 9.8f;//最大重力
    float GravityAccelertion = 0.1f;//重力の加速率
public:
    bool isGoal_;
    Player(GameObject* parent);
    ~Player();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    void OnCollision(GameObject* pTarget)override;
    void Fall();
    //void ResetAnimFirstFrame(int animIndex);
};


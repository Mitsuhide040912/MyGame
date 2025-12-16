#pragma once
#include "Engine/GameObject.h"
#include "Item.h"
class Player :
    public GameObject
{
    int hModel_;
    int hModelanime_[3];
    int fall_;
    int camState_;//カメラタイプの指定
    int animType_;//アニメーションのタイプの指定
    int hSound_;//音のデータ

    bool canMove_;
    bool hModelanim_;
    bool nextAnimState_;
    bool thisFall_;
    bool thisThrow_;
    bool isItem_;
    bool throwStone_;

    float prevDist_;
    float fallDist_;
    float timer_;
    float fallTime;
    float frontRayDist_;
    float wallDist_;
    float speed_ = 50;
    float itemDir;


    const int ANIM_STRT_FRAME = 1;
    const int ANIM_END_SPEED = 1;
    const int ANIM_Idle_FRAME = 600;
    const int ANMI_Running_FRAME = 50;
    const int ANIM_Pickup_FRAME = 63;

    const float THROW_TIME = 0.7;
    //レイの位置
    const float RAY_START_HEIGHT = 4.0f;
    //プレイヤーの初期化
    const float PLAYER_IMIT_ROT_Y = 180.0f;
    const XMFLOAT3 PLAYER_INIT_SCALE = { 3.5f,3.5f,3.5f };
    const XMFLOAT3 PLAYER_INIT_POS = { -75.0f,-110.0f,-20.0f };
    //移動・速度
    const float PLAYER_SPEED = 350.0f;
    const float PLAYER_FALL_SPEED = 15.0f;
    //投げる石
    const float BULLET_SPEED = 35.0f;
    const float BULLET_GRAVITY = 15.0f;
    //ステージ制限
    const float PLAYER_DETH_HEIGHT = -157.0f;
    //ステージの端制限
    const float STAGE_X_MIN = -110.0f;
    const float STAGE_X_MAX = 235.0f;
    const float STAGE_Z_MIN = -190.0f;
    const float STAGE_Z_MAX = 190.0f;
    

    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    XMVECTOR front_;
    XMMATRIX WorldMatrix;//自分のワールド行列
    Item* CarryItem = nullptr;//今持ってるアイテム


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
    bool GetItemState() { return isItem_; }
};


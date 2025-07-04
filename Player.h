#pragma once
#include "Engine/GameObject.h"
#include "Item.h"
class Player :
    public GameObject
{
    int hModel_;
    int hModelanime_[3];
    int fall_;
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
    XMVECTOR front_;

    float frontRayDist_;
    float wallDist_;

    float speed_ = 50;
    int camState_;//カメラタイプの指定
    int animType_;//アニメーションのタイプの指定
    //XMFLOAT3 f;
    //XMVECTOR v = XMLoadFloat3(&f);

    const int ANIM_STRT_FRAME = 1;
    const int ANIM_END_SPEED = 1;
    const int ANIM_Idle_FRAME = 600;
    const int ANMI_Running_FRAME = 50;
    const int ANIM_Pickup_FRAME = 66;

    const float THROW_TIME = 1.1;
    

    XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    XMMATRIX WorldMatrix;//自分のワールド行列
    Item* CarryItem = nullptr;//今持ってるアイテム

    float itemDir;
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


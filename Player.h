#pragma once
#include "Engine/GameObject.h"
class Player :
    public GameObject
{
    int hModel_;
    int hModelanime_[3];
    //XMVECTOR float_;
    XMVECTOR front_;
    float speed_;
    int camState_;//カメラタイプの指定
    int animType_;//アニメーションのタイプの指定
    XMFLOAT3 f;
    XMVECTOR v = XMLoadFloat3(&f);
    bool isItem_;
  
public:
    bool isGoal_;
    Player(GameObject* parent);
    ~Player();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    void OnCollision(GameObject* pTarget)override;
    
};


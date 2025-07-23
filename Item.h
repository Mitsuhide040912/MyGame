#pragma once
#include "Engine/GameObject.h"
class Item :
    public GameObject
{
    int hModel_;
    XMMATRIX LocalMatrix = XMMatrixIdentity();
    XMMATRIX WorldMatrix = XMMatrixIdentity();
    Item* CarryItem = nullptr;//今持ってるアイテム
    float x, y, z;

    //アイテムの初期化
    const XMFLOAT3 EGG_INIT_SCALE = { 0.8f,0.8f,0.8f };
    const XMFLOAT3 EGG_INIT_POS = { -75.0f,0,160.0f };

public:

    Item(GameObject* parent);
    ~Item();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    void OnCollision(GameObject* pTarget)override;
    void SetTransform(XMFLOAT3 position, XMFLOAT3 rotation) { 
        transform_.position_ = position;
        transform_.rotate_ = rotation;
    }
};


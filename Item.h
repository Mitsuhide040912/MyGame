#pragma once
#include "Engine/GameObject.h"
class Item :
    public GameObject
{
    float speed_;
    XMVECTOR front_;

    int hModel_;
    XMMATRIX LocalMatrix = XMMatrixIdentity();
    XMMATRIX WorldMatrix = XMMatrixIdentity();
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


#pragma once
#include "Engine/GameObject.h"
class Item :
    public GameObject
{
    float speed_;
    XMVECTOR front_;

    int hModel_;
    XMMATRIX WorldItemMatrix;
public:

    Item(GameObject* parent);
    ~Item();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    void OnCollision(GameObject* pTarget)override;
    void SetWorldMatrix(const XMMATRIX mat) { WorldItemMatrix = mat; }
    const XMMATRIX& GetWorldMatrix()const { return WorldItemMatrix; }
};


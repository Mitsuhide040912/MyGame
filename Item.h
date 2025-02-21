#pragma once
#include "Engine/GameObject.h"
class Item :
    public GameObject
{
    int hModel_;
public:

    Item(GameObject* parent);
    ~Item();
    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;
    void OnCollision(GameObject* pTarget)override;
};


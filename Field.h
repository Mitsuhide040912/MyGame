#pragma once
#include "Engine/GameObject.h"
class Field :
    public GameObject
{
    int hModel_;
public:
    Field(GameObject* parent);
    ~Field();

    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;

    int GetModelHandle() { return hModel_; }
};



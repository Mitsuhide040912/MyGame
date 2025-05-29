#pragma once
#include "Engine/GameObject.h"
class Field :
    public GameObject
{
    int hModel_;
    int hField_[4];
    int hField_1;
    int hField_2;
    int hField_3;
    int hField_4;
public:
    Field(GameObject* parent);
    ~Field();

    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;

    int GetModelHandle() { return hModel_; }
};



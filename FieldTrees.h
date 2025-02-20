#pragma once
#include "Engine/GameObject.h"
class FieldTrees :
    public GameObject
{
    int hModel_;
public:
    FieldTrees(GameObject* parent);
    ~FieldTrees();

    void Initialize()override;
    void Update()override;
    void Draw()override;
    void Release()override;

};


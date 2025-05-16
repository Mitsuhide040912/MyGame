#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>
using namespace DirectX;

class EnemyAI :
    public GameObject
{
public:
    static bool IsEnemyTarget(
        const DirectX::XMFLOAT3& enemyPosition,
        const DirectX::XMFLOAT3& enemyForward,
        const DirectX::XMFLOAT3& targetPosition,
        float Degrees,
        float maxViewDistance
    );
};


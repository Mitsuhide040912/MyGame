#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>
#include <vector>
using namespace DirectX;

class EnemyAI :
    public GameObject
{
    std::vector<XMFLOAT3>patrolPoint;//パトロールの地点
    int currentPointIndex_ = 0;
public:
    static bool IsEnemyTarget(
        const DirectX::XMFLOAT3& enemyPosition,
        const DirectX::XMFLOAT3& enemyForward,
        const DirectX::XMFLOAT3& targetPosition,
        float Degrees,
        float maxViewDistance
    );
};


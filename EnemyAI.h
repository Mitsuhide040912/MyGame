#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>
#include <vector>
using namespace DirectX;

class EnemyAI :
    public GameObject
{
public:
    EnemyAI();

    void AddPatrolPoint(const DirectX::XMFLOAT3& point);
    const DirectX::XMFLOAT3& GetCurrentPatrolPoint()const;

    bool HasRenchPoint(const DirectX::XMFLOAT3& currentPos)const;
    void NextPoint();
    static bool IsEnemyTarget(
        const DirectX::XMFLOAT3& enemyPosition,
        const DirectX::XMFLOAT3& enemyForward,
        const DirectX::XMFLOAT3& targetPosition,
        float Degrees,
        float maxViewDistance
    );
    void Update()override;
    void Draw()override;
    void Initialize()override;
    void Release()override;
private:
    XMFLOAT3 position_;//�G�̌��݈ʒu
    std::vector<XMFLOAT3>patrolPoint;//�p�g���[���̒n�_

    int currentPointIndex_ = 0;


    float arrivalThreshold_ = 0.3f;
};


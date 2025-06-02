#include "EnemyAI.h"
#include <cmath>
#include <DirectXMath.h>

using namespace DirectX;

EnemyAI::EnemyAI()
{
}

void EnemyAI::AddPatrolPoint(const DirectX::XMFLOAT3& point)
{
	patrolPoint.push_back(point);
}

const DirectX::XMFLOAT3& EnemyAI::GetCurrentPatrolPoint() const
{
	return patrolPoint[currentPointIndex_];
}

bool EnemyAI::HasRenchPoint(const DirectX::XMFLOAT3& currentPos) const
{
	XMVECTOR cur = XMLoadFloat3(&currentPos);
	XMVECTOR target = XMLoadFloat3(&patrolPoint[currentPointIndex_]);
	float dist = XMVectorGetX(XMVector3Length(XMVectorSubtract(target, cur)));
	return dist < arrivalThreshold_;
}

void EnemyAI::NextPoint()
{
	if (patrolPoint.empty())return;
	currentPointIndex_ = (currentPointIndex_ + 1) % patrolPoint.size();
}

bool EnemyAI::IsEnemyTarget(const DirectX::XMFLOAT3& enemyPosition, const DirectX::XMFLOAT3& enemyForward, const DirectX::XMFLOAT3& targetPosition, float Degrees, float maxViewDistance)
{
	XMVECTOR posEnemy = XMLoadFloat3(&enemyPosition);
	XMVECTOR dirEnemy = XMVector3Normalize(XMLoadFloat3(&enemyForward));
	XMVECTOR posTarget = XMLoadFloat3(&targetPosition);

	XMVECTOR toTarget = XMVectorSubtract(posTarget, posEnemy);
	//‹——£‚ðŒvŽZ
	float distance = XMVectorGetX(XMVector3Length(toTarget));
	//‹——£‚ð”»’è
	if (distance > maxViewDistance)
		return false;
	toTarget = XMVector3Normalize(toTarget);
	float dot = XMVectorGetX(XMVector3Dot(dirEnemy, toTarget));

	float cosThereshold = cosf(XMConvertToRadians(Degrees / 5.0f));
	return dot >= cosThereshold;
}

void EnemyAI::Update()
{
}

void EnemyAI::Draw()
{
}

void EnemyAI::Initialize()
{
}

void EnemyAI::Release()
{
}


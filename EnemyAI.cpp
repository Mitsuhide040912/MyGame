#include "EnemyAI.h"
#include <cmath>

using namespace DirectX;

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

	float cosThereshold = cosf(XMConvertToRadians(Degrees / 2.0f));
	return dot >= cosThereshold;
}

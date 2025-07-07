#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/time.h"
#include "Engine/SphereCollider.h"
#include <cassert>
#include <cmath>
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet")
	,hModel_(-1),velocity_(XMVectorZero()),gravity_(-6.0f)
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Model\\Bullet.fbx");
	assert(hModel_ >= 0);
	SphereCollider* collider = new SphereCollider({ 0,0,0 }, 0.5);
	AddCollider(collider);
}



void Bullet::Update()
{	
	float deltaTime = Time::DeltaTime();

	velocity_ += XMVectorSet(0, gravity_ * deltaTime, 0, 0);
	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	pos += velocity_ * deltaTime;
	XMStoreFloat3(&transform_.position_, pos);

	//«y‚ª-140‚ğ’´‚¦‚½“_‚ÅÎ‚ğÁ‹
	if (transform_.position_.y < -140.0f) {
		KillMe();
	}
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}


void Bullet::SetVelocity(const DirectX::XMFLOAT3& dir, float speed, float angreDigrees)
{
	XMVECTOR horaizonalDir = XMVector3Normalize(XMVectorSet(dir.x, 0, dir.z, 0));
	float angleRad = cosf(angreDigrees);
	float cosA = cosf(angleRad);
	float sinA = sinf(angleRad);


	XMVECTOR horizonalVel = horaizonalDir * (speed * cosA);
	XMVECTOR verticalVel = XMVectorSet(0, speed * sinA, 0, 0);

	velocity_ = horizonalVel + verticalVel;
}
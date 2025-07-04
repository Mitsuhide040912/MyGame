#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/time.h"
#include "Engine/SphereCollider.h"
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"),hModel_(-1)
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Model\\Bullet.fbx");
	assert(hModel_ >= 0);
	
}

void Bullet::Update()
{
	transform_.position_.x = transform_.position_.x + moveDir_.x * bulletSpeed_;
	transform_.position_.y = transform_.position_.y + moveDir_.y * bulletSpeed_;
	transform_.position_.z = transform_.position_.z + moveDir_.z * bulletSpeed_;
	moveDir_ = { moveDir_.x,moveDir_.y - 0.1f,moveDir_.z };
	
}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}

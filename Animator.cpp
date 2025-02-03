#include "Animator.h"
#include "Engine/Direct3D.h"
#include "Engine/Model.h"

Animator::Animator()
{
	attachIndex = -1;
	frameSpeed = 0.2f;
}

Animator::~Animator()
{
	//if (attachIndex >= 0)
	//	Model::Load(baseModel, attachIndex);
}

void Animator::Update()
{
}

void Animator::SetModel(int model)
{
}

void Animator::Play(int animModel, bool loop)
{
}

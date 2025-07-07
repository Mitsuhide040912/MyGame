#pragma once
#include "Engine/GameObject.h"
#include <DirectXMath.h>
class Bullet :
    public GameObject
{
	int hModel_;
	DirectX::XMVECTOR velocity_;
	float gravity_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Bullet(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	
	void SetVelocity(const DirectX::XMFLOAT3& dir, float speed, float angreDigrees);
};


#pragma once
#include "Engine/GameObject.h"
class GoalFrag :
    public GameObject
{
	int hModel_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GoalFrag(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* pTarget)override;
};


#pragma once
#include "Engine/GameObject.h"
class Timer :
    public GameObject
{
	float timer_;//����������
	bool isTimeUp_;//�����Ԑ؂ꂩ�ǂ������f
	int hImage_;
	float x, y, z;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Timer(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void DrawDigit(int digit, float posX, float posY);
};


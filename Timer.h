#pragma once
#include "Engine/GameObject.h"
class Timer :
    public GameObject
{

	int timer_;//����������
	int hImage_;
	int tenMin_;
	int min_;
	int tenSec_;
	int sec_;
	int cutOutRangeY = 30;
	int cutOutRangewidth = 50;
	int cutOutRangeheight = 90;

	float oneSec_;

	bool isTimeUp_;//�����Ԑ؂ꂩ�ǂ������f

	const float IMAGE_WIDTH = 51.2;
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
};


#pragma once
#include "Engine/GameObject.h"
class TitleScene :
    public GameObject
{
	int hImege_;
	int select_;//�I��
	int prevUpKey_;//�O�t���[���̏�L�[
	int prevDownKey_;//�O�t���[���̉��L�[
	int hSound_;//�T�E���h�ԍ�

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


#pragma once
#include "Engine/GameObject.h"
class ManualScene :
    public GameObject
{
	int hImege_;
	int select_;//�I��
	int prevUpKey_;//�O�t���[���̏�L�[
	int prevDownKey_;//�O�t���[���̉��L�[

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ManualScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};


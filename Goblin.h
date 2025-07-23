#pragma once
#include "Engine/GameObject.h"
#include <vector>

class Goblin :
    public GameObject
{
	int hModel_;
	int hModelAnimeGob_[2];
	int animType_;
	int isHit_ = 0;

	float gobSpeed_ = 0.16f;
	float angle = 160.0f;
	float maxDistance = 30.0f;

	bool rotateClockwise_ = true;
	bool hitFrag_;

	//�S�u�����̏�����
	const XMFLOAT3 GOB_INIT_SCALE = { 2.5f,2.5f,2.5f };
	//�S�u�����̃t���[��
	const int ANIM_STRT_FRAME = 1;
	const int ANIM_END_SPEED = 1;
	const int ANIM_Idle_FRAME = 183;
	const int ANIM_Walk_FRAME = 48;
	//�S�u����������y�̒l�𒴂��Ă�����폜
	const float GOBLIN_DETH_HEIGHT = -150.0f;
	//Maya�ō�������f���̊p�x���኱����Ă��邽��
	const float mayaCorection = 5.0f;

	
public:
	Goblin(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw()override;



	//�J��
	void Release() override;

	void SetPosition(const XMFLOAT3& pos);

	void SetRotateDir(bool clockWise);

	void OnCollision(GameObject* pTarget)override;
};


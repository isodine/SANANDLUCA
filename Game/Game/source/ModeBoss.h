#pragma once
#include "appframe.h"
#include "Boss.h"

class SAN;
class LKA;

class ModeBoss : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	VECTOR TargetPos;  //�^�[�Q�b�g�̃|�W�V����
	VECTOR TargetDir;  //�^�[�Q�b�g�̌���
	int SanLka;  //�T���ƃ��J�̂ǂ�����^�[�Q�b�g�ɂ��邩
	int WalkCount;  //�����Ēǂ���������

	int StageHandle;
	int frameMapCollisionwall;
	int frameMapCollisionfloor;
	
	VECTOR	_vPos;					// �ʒu
	VECTOR	_vTarget;				// ����
	float	_clipNear, _clipFar;	// �N���b�v

protected:
	Boss boss;
	SAN san;
	LKA lka;
	Camera _cam;
	SanBomb sanbomb;
	Damage damage;
};
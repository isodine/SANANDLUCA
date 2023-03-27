#pragma once

#include "appframe.h"
#include "BossSwamp.h"
#include "Damage.h"

class ModeBoss;
class SAN;
class LKA;
class SanBomb;
class LkaBomb;

class Boss {
public:
	void Initialize();
	void Terminate();
	void Process(Damage& damage);
	void Render();

	void Targeting(VECTOR sanPos, VECTOR lkaPos);
	void Rush(VECTOR sanPos, VECTOR lkaPos, int SanHandle, int LkaHandle, int MapHandle);
	void Capture();
	void CaptureEnd();
	void Rotation(VECTOR sanPos, VECTOR lkaPos);
	void Walk();
	void Crush();		//�ǏՓˎ�����
	void Search();
	void Down();
	void Idle();
	void Pull();
	void SwampSpawn(bool IsSan);

	int Target;
	VECTOR BossPos;
	VECTOR BossSetDir;
	VECTOR BossDir;
	VECTOR RightHandPos;
	VECTOR LeftHandPos;
	VECTOR HandPos;
	VECTOR AddPos;
	VECTOR TargetDir;
	VECTOR SphereCenter;
	VECTOR BossPosition0;
	VECTOR BossPosition1;
	VECTOR BossPosition2;
	VECTOR BossPosition3;
	//VECTOR SwampPos;
	int handleBaseSan;
	int handleBaseLka;
	VECTOR swampDir;
	VECTOR swampDegreeDir;
	int SwampCnt;

	MATRIX rotationMatrix;
	VECTOR forward;

	enum class BOSSTYPE {
		NONE,
		RUSH,
		CAPTURE,
		CAPTUREEND,
		ROTATION,
		WALK,
		CRUSH,
		SEARCH,
		PULL,
		DOWN,
		IDLE,
	};

	BOSSTYPE type;

	enum class PH {
		ACID,
		ALCALI,
		NONE,
	};

	PH phType;
	PH oldphType;
	
	int RotateCount;//��]���鎞��
	int WaitCount;//���ߍU���̃��[�V�����̃J�E���g
	int PullCount;//������܂ł̕b��
	int CrushCount;//�����΂����鎞��
	int IdleCount;//�x�e���鎞��
	int CaptureCount;//�߂܂��Ă��鎞��
	int EndCount;//�߂܂�����̎���
	int DownCount;//���ꂽ���̎���
	int BossHP;//�{�X�̗̑�
	float PlayTime;
	int randomNum;
	int walkRand;
	int walkTimeCount;

	float StopDir;//��]���~�܂�덷
	float StopPos;//�~�܂�ꏊ�̌덷
	float rotate;//��]���鑬�x

	bool rotateFlag;//TRUE�Ȃ��]����
	bool walkFlag;//TRUE�Ȃ����
	bool rushFlag;//TRUE�Ȃ�U����������U���Ɉڂ�
	bool targetFlag;//TRUE�Ȃ�U���̃^�[�Q�b�g�����߂�
	bool target;//TRUE�Ȃ�T���ɍU��
	bool idleFlag;//TRUE�Ȃ�A�C�h�����[�V����
	bool SanCatchFlag;//TRUE�Ȃ�T����߂܂���
	bool LkaCatchFlag;//TRUE�Ȃ烋�J��߂܂���
	bool crushFlag;//TRUE�Ȃ�TYPE��Crash�ɂ���
	bool AttackedFlag;//TRUE�Ȃ�U�����ꂽ
	bool searchFlag;//TRUE�Ȃ��ʒu�����߂�
	bool downFlag;//TRUE�Ȃ���ꂽ
	bool sanhitEf;//TRUE�Ȃ�_���[�W�G�t�F�N�g�o��
	bool lkahitEf;//TRUE�Ȃ�_���[�W�G�t�F�N�g�o��
	bool bosshitEf;//TRUE�Ȃ�_���[�W�G�t�F�N�g�o��
	bool bossdownEf;//TRUE�Ȃ�_�E���G�t�F�N�g�o��

	int acidHandle;//�_���̂Ƃ��̃e�N�X�`��
	int alcaliHandle;//�A���J�����̂Ƃ��̃e�N�X�`��
	int noneHandle;//�����̎��̃e�N�X�`��

	int Key1P;
	int Trg1P;
	int key;
	int trg;

	SAN* san;
	LKA* lka;
	SanBomb* sanB;
	LkaBomb* lkaB;
	ModeBoss* modeboss;
	modelInf model;
	modelManager* manager;
	BossSwamp Bswamp;
	std::vector<std::unique_ptr<BossSwamp>> swamps;
};
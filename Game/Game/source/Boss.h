#pragma once

#include "appframe.h"

class ModeBoss;
class SAN;
class LKA;

class Boss {
public:
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	void Targeting(VECTOR sanPos, VECTOR lkaPos);
	void Rush(VECTOR sanPos, VECTOR lkaPos, int SanHandle, int LkaHandle, int MapHandle);
	void Capture();
	void CaptureEnd();
	void Rotation(VECTOR sanPos, VECTOR lkaPos);
	void Walk();
	void Crush();
	void Down();
	void Idle();
	void Pull();

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
		PULL,
		DOWN,
		IDLE,
	};

	BOSSTYPE type;
	
	int RotateCount;//��]���鎞��
	int WaitCount;//���ߍU���̃��[�V�����̃J�E���g
	int PullCount;//������܂ł̕b��
	int CrushCount;//�����΂����鎞��
	int IdleCount;//�x�e���鎞��
	int CaptureCount;//�߂܂��Ă��鎞��
	int EndCount;//�߂܂�����̎���
	int BossHP;//�{�X�̗̑�
	float TotalTime1;
	float TotalTime2;
	float TotalTime3;
	float PlayTime;
	int randomNum;
	int walkRand;
	int walkTime0;
	int walkTime1;
	int walkTime2;
	int WalkTime;
	int walkTimeCount;

	float StopDir;
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
	

	SAN* san;
	LKA* lka;
	ModeBoss* modeboss;
	modelInf model;
	modelManager* manager;
};
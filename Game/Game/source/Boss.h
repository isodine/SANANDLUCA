#pragma once

#include "appframe.h"
class Boss {
public:
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	void Rush(VECTOR sanPos, VECTOR lkaPos, VECTOR sanDir, VECTOR lkaDir);
	void Capture();
	void Rotation(VECTOR sanPos, VECTOR lkaPos, VECTOR sanDir, VECTOR lkaDir);
	void Walk();
	void Crush();
	void Down();
	void Idle();

	int Target;
	VECTOR BossPos;
	VECTOR BossSetDir;
	VECTOR BossDir;
	VECTOR RightHandPos;
	VECTOR LeftHandPos;
	VECTOR HandPos;
	VECTOR AddPos;
	VECTOR TargetDir;

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
	
	int BossHandle;
	int AttachAnim1;
	int AttachAnim2;
	int AttachAnim3;
	int rotateCount;
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
	bool idleflag;//TRUE�Ȃ�A�C�h�����[�V����
	

	SAN san;
	LKA lka;
	modelInf model;
	modelManager* manager;
};
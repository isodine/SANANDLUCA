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
	
	int RotateCount;//回転する時間
	int WaitCount;//ため攻撃のモーションのカウント
	int PullCount;//抜けるまでの秒数
	int CrushCount;//じたばたする時間
	int IdleCount;//休憩する時間
	int CaptureCount;//捕まえている時間
	int EndCount;//捕まえた後の時間
	int BossHP;//ボスの体力
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
	float rotate;//回転する速度

	bool rotateFlag;//TRUEなら回転する
	bool walkFlag;//TRUEなら歩く
	bool rushFlag;//TRUEなら攻撃準備から攻撃に移る
	bool targetFlag;//TRUEなら攻撃のターゲットを決める
	bool target;//TRUEならサンに攻撃
	bool idleFlag;//TRUEならアイドルモーション
	bool SanCatchFlag;//TRUEならサンを捕まえた
	bool LkaCatchFlag;//TRUEならルカを捕まえた
	bool crushFlag;//TRUEならTYPEをCrashにする
	bool AttackedFlag;//TRUEなら攻撃された
	

	SAN* san;
	LKA* lka;
	ModeBoss* modeboss;
	modelInf model;
	modelManager* manager;
};
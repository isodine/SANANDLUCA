#pragma once

class modelInf;

class Boss {
public:
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	void Rush();
	void Capture();
	void Rotation();
	void Walk();
	void Crush();
	void Down();

	int Target;
	VECTOR BossPos;
	VECTOR BossSetDir;
	VECTOR BossDir;
	VECTOR RightHandPos;
	VECTOR LeftHandPos;
	VECTOR HandPos;

	enum class BOSSTYPE {
		NONE,
		RUSH,
		CAPTURE,
		ROTATION,
		WALK,
		CRUSH,
		DOWN,
	};

	BOSSTYPE type;
	
	int BossHandle;
	int AttachAnim1;
	int AttachAnim2;
	int AttachAnim3;
	float TotalTime1;
	float TotalTime2;
	float TotalTime3;
	float PlayTime;
	int randomNum;
	int walkRand;

	float StopDir;

	bool rotateFlag;
	bool walkFlag;

	SAN* san;
	LKA* lka;
	modelInf* model;
	modelManager* manager;
};
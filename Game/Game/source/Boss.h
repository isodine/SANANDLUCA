#pragma once

class Boss {
public:
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	void Rush();
	void Capture();
	void Walk();
	void Turn();
	void Crush();
	void Down();

	int Target;
	VECTOR BossPos;
	VECTOR RightHandPos;
	VECTOR LeftHandPos;
	VECTOR HandPos;
	
	int BossHandle;

	SAN* san;
	LKA* lka;
};
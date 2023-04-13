#pragma once

class Elevator
{
public:
	Elevator();
	~Elevator();
	void Initialize();
	void Update(Electrode& electr);
	void Terminate();
	void Render();
	void Move();

	// 3Dモデル描画用
	int handle;
	int handleCol;
	VECTOR vPos;		// 位置
	VECTOR vPosfirst;
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//動くスピード
	float upRange = 200.f;
	float downRange = 0.f;
	bool floating = false;
	bool moving = false;
};

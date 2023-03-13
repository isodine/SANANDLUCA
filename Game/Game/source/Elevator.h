#pragma once
#pragma once
class Elevator
{
public:
	Elevator();
	~Elevator();
	void Initialize();
	void Update(Electrode& electr);
	void Render();
	void Move();

	// 3Dモデル描画用
	int handle;
	VECTOR vPos;		// 位置
	VECTOR vPosfirst;
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//動くスピード
	float upRange = 100.f;
	float downRange = 0.f;
	bool floating = true;
	bool moving = false;
};

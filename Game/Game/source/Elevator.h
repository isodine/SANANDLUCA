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

	// 3D���f���`��p
	int handle;
	int handleCol;
	VECTOR vPos;		// �ʒu
	VECTOR vPosfirst;
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//�����X�s�[�h
	float upRange = 200.f;
	float downRange = 0.f;
	bool floating = false;
	bool moving = false;
};

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

	// 3D���f���`��p
	int handle;
	VECTOR vPos;		// �ʒu
	VECTOR vPosfirst;
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//�����X�s�[�h
	float upRange = 100.f;
	float downRange = 0.f;
	bool floating = true;
	bool moving = false;
};

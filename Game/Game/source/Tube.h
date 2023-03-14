#pragma once

class Tube
{
public:
	Tube();
	~Tube();
	void Initialize(int Type, VECTOR Pos);
	void Update(Electrode& electr);
	void Render();
	void Spin();

	// 3D���f���`��p
	int handle;
	int handleCol;
	VECTOR vPos;		// �ʒu
	VECTOR vDir;			// ����
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//�����X�s�[�h
	float rightRange = 90.f;
	float leftRange = -90.f;
	float frontRange = 0.f;
	bool spining = false;

	//�������Ă������
	enum TubeType
	{
		Neutrality,
		San,
		Lka
	};
	TubeType Type;

	//�������Ă������
	enum DirType
	{
		Front,
		Right,
		Left
	};
	DirType Dir;
};

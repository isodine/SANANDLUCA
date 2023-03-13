#pragma once

class Tube
{
public:
	Tube();
	~Tube();
	void Initialize(int Type);
	void Update(Electrode& electr);
	void Render();
	void Spin();

	// 3Dモデル描画用
	int handle;
	int handleCol;
	VECTOR vPos;		// 位置
	VECTOR vDir;			// 向き
	VECTOR vPosfirst;
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//動くスピード
	float rightRange = -180.f;
	float leftRange = 180.f;
	bool spining = false;

	//今向いている方向
	enum TubeType
	{
		Neutrality,
		San,
		Lka
	};
	TubeType Type;

	//今向いている方向
	enum DirType
	{
		Front,
		Right,
		Left
	};
	DirType Dir;
};

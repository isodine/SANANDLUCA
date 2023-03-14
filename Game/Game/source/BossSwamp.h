#pragma once
class BossSwamp
{
public:
	BossSwamp();
	~BossSwamp();
	void Initialize();
	void Update();
	void Render();

	// 3Dモデル描画用
	int handle;
	VECTOR vPos;	// 位置
	int handleCol;
	int handleSANswamp;
	int handleLKAswamp;
	bool isSan = true;     //trueならサン、falseならルカ

};

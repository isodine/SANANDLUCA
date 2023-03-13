#pragma once
class Electrode
{
public:
	Electrode();
	~Electrode();
	void Initialize(VECTOR Pos,bool is_san);
	void Update(SanBomb& sanbomb, LkaBomb& lkabomb);
	void Render();

	// 3Dモデル描画用
	int handle;
	VECTOR vPos;	// 位置
	int handleCol;
	int handleSANelectrode;
	int handleLKAelectrode;
	bool isSan = true;     //trueならサン、falseならルカ
	bool change = false;
};

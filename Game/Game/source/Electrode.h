#pragma once
class Electrode
{
public:
	Electrode();
	~Electrode();
	void Initialize(VECTOR Pos,bool is_san);
	void Update(SanBomb& sanbomb, LkaBomb& lkabomb);
	void Render();

	// 3D���f���`��p
	int handle;
	VECTOR vPos;	// �ʒu
	int handleCol;
	int handleSANelectrode;
	int handleLKAelectrode;
	bool isSan = true;     //true�Ȃ�T���Afalse�Ȃ烋�J
	bool change = false;
};

#pragma once
class BossSwamp
{
public:
	BossSwamp();
	~BossSwamp();
	void Initialize();
	void Update();
	void Render();

	// 3D���f���`��p
	int handle;
	VECTOR vPos;	// �ʒu
	int handleCol;
	int handleSANswamp;
	int handleLKAswamp;
	bool isSan = true;     //true�Ȃ�T���Afalse�Ȃ烋�J

};

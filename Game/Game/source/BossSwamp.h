#pragma once
class BossSwamp
{
public:
	//BossSwamp();
	//~BossSwamp();
	void ModelInitialize();
	void Initialize(bool IsSan,VECTOR Pos,int handleSan, int handleLka);
	void Update(std::vector<std::unique_ptr<BossSwamp>>& swamps);
	void Render();

	// 3D���f���`��p
	int handleBaseSan;
	int handleBaseLka;
	int handle;
	VECTOR vPos;	// �ʒu
	int handleCol;
	bool isSan = true;     //true�Ȃ�T���Afalse�Ȃ烋�J
	bool neutralization = false;		//true�Ȃ璆�a�����Afalse�Ȃ璆�a���ĂȂ�(���a=������)
	float diameter = 90;		//���a�̒���
};

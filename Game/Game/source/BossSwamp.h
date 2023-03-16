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

	// 3Dモデル描画用
	int handleBaseSan;
	int handleBaseLka;
	int handle;
	VECTOR vPos;	// 位置
	int handleCol;
	bool isSan = true;     //trueならサン、falseならルカ
	bool neutralization = false;		//trueなら中和した、falseなら中和してない(中和=消える)
	float diameter = 90;		//直径の長さ
};

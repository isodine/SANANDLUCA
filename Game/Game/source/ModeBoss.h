#pragma once
#include "appframe.h"
#include "Boss.h"

class ModeBoss : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void Walk();
	void Target();
	void Rush();
	void Crush();
	void Capture();
	void Down();

	VECTOR TargetPos;  //ターゲットのポジション
	VECTOR TargetDir;  //ターゲットの向き
	int SanLka;  //サンとルカのどちらをターゲットにするか
	int WalkCount;  //歩いて追いかけた回数


protected:
	Boss boss;
	SAN* san;
	LKA* lka;
};
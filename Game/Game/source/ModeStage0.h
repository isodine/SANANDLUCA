#pragma once
#include "appframe.h"

class ModeStage0 : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	int handle;
	int Mattach_index;
	// 3Dモデル描画用
	float Mtotal_time;
	float Mplay_time;
	VECTOR _vPos;	// 位置
	VECTOR _vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）
};
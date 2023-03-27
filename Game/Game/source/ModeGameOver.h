#pragma once
#include "appframe.h"

class ModeGameOver : public ModeBase {
	typedef ModeBase base;
public:
	ModeGameOver(int num);
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	int StageNum;
};
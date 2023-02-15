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

	Boss boss;
};
#pragma once
#include "appframe.h"

class ModeTitle : public ModeBase {
	typedef ModeBase base;
public:
	ModeTitle();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	
	int titleHandle;
	int SEcrik;
};
#pragma once
#include "appframe.h"

class ModeEnding : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
private:
	int IsPlaying;
	int Endinghandle;
};
#pragma once
#include "appframe.h"

class ModeGameOver : public ModeBase {
	typedef ModeBase base;
public:
	ModeGameOver(int num, bool flag);
	ModeGameOver();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	bool timeupFlag;//�^�C���A�b�v����TRUE�ɂȂ�

private:
	int IsPlaying;
	int StageNum;
	int Gameoverhandle;
	int TimeUphandle;
	
};
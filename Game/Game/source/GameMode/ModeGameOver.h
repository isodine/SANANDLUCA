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

	bool timeupFlag;//タイムアップ時にTRUEになる

private:
	int IsPlayingGameOver;
	int IsPlayingTimeUp;
	int StageNum;
	int Gameoverhandle;
	int TimeUphandle;
	
};
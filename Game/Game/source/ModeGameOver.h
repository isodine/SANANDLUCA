#pragma once
#include "appframe.h"

class ModeGameOver : public ModeBase {
	typedef ModeBase base;
public:
	ModeGameOver(int num);
	ModeGameOver();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	bool timeupFlag;//タイムアップ時にTRUEになる
	bool gameoverFlag;//体力ゼロ、落下時にTRUEになる

private:
	int IsPlaying;
	int StageNum;
	int Gameoverhandle;
	int TimeUphandle;
	
};
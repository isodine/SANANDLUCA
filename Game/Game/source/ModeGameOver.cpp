#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeGameOver.h"
#include "ModeStage1.h"
#include "ModeStage2.h"
#include "ModeStage3.h"
#include "ModeBoss.h"
#include "ModeTitle.h"
//#include "ModeGame.h"


bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }
	Gameoverhandle = LoadGraph("res/GameOver.mp4");
	IsPlaying = 1;
	return true;
}

bool ModeGameOver::Terminate() {
	base::Terminate();

	return true;
}

bool ModeGameOver::Process() {
	base::Process();

	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_PAD1);
	Trg = (Key ^ keyold) & Key;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）

	if (Trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}
	IsPlaying = GetMovieStateToGraph(Gameoverhandle);
	if (IsPlaying == 0)
	{
		PauseMovieToGraph(Gameoverhandle);
	}
	return true;
}

bool ModeGameOver::Render()
{
	PlayMovieToGraph(Gameoverhandle);
	DrawGraph(0, 0, Gameoverhandle,false);

	return true;
}
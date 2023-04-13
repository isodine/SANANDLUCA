#include "AppFrame.h"
#include "ModeGameOver.h"
#include "ModeStage1.h"
#include "ModeStage2.h"
#include "ModeStage3.h"
#include "ModeBoss.h"
#include "ModeTitle.h"

ModeGameOver::ModeGameOver(int num, bool flag) {
	StageNum = num;
	timeupFlag = flag;
}

ModeGameOver::ModeGameOver() {
	
}

bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }
	TimeUphandle = LoadGraph("res/TimeUp.mp4");
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

	if (Trg & PAD_INPUT_1 && StageNum == 0) {
		timeupFlag = false;
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage0(), 1, "stage00");
	}
	else if (Trg& PAD_INPUT_1&& StageNum == 1) {
		timeupFlag = false;
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "stage01");
	}
	else if (Trg & PAD_INPUT_1 && StageNum == 3) {
		timeupFlag = false;
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeBoss(), 1, "boss");
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
	PlayMovieToGraph(TimeUphandle);
	if (timeupFlag) {
		DrawGraph(0, 0, TimeUphandle, false);
	}
	else{
		DrawGraph(0, 0, Gameoverhandle, false);
	}
	

	return true;
}
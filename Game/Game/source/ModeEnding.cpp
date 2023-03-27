#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeEnding.h"
#include "ModeTitle.h"

bool ModeEnding::Initialize() {
	if (!base::Initialize()) { return false; }
	Endinghandle = LoadGraph("res/99_Credit.mp4");
	return true;
}

bool ModeEnding::Terminate() {
	base::Terminate();

	return true;
}

bool ModeEnding::Process() {
	base::Process();

	//仮
	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg = (Key ^ keyold) & Key;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）

	int checkKey = /*PAD_INPUT_1 | PAD_INPUT_2 |*/ PAD_INPUT_3 | PAD_INPUT_4 | PAD_INPUT_5 | PAD_INPUT_6 | PAD_INPUT_7 | PAD_INPUT_8 | PAD_INPUT_9 | PAD_INPUT_10;


	if (Trg & checkKey) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}
	IsPlaying = GetMovieStateToGraph(Endinghandle);
	if (IsPlaying == 0)
	{
		PauseMovieToGraph(Endinghandle);
	}

	return true;
}

bool ModeEnding::Render() {
	PlayMovieToGraph(Endinghandle);
	DrawGraph(0, 0, Endinghandle, false);

	return true;
}
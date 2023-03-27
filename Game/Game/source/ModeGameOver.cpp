#include "AppFrame.h"
#include "ModeGameOver.h"
#include "ModeStage1.h"
#include "ModeStage2.h"
#include "ModeStage3.h"
#include "ModeBoss.h"
#include "ModeTitle.h"

ModeGameOver::ModeGameOver(int num) {
	StageNum = num;
}

bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }

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
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage0(), 1, "stage00");
	}
	else if (Trg& PAD_INPUT_1&& StageNum == 1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "stage01");
	}
	return true;
}

bool ModeGameOver::Render() {
	DrawString(0, 0, "ゲームオーバー", GetColor(255, 255, 255));

	return true;
}
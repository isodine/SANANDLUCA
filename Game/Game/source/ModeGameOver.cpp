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
	Grhandle = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_20.png");
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
	Trg = (Key ^ keyold) & Key;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	if (Trg & PAD_INPUT_1) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
		//ModeServer::GetInstance()->Add(new ModeBoss(), 1, "boss");
	}
	return true;
}

bool ModeGameOver::Render() {
	DrawString(0, 0, "�Q�[���I�[�o�[", GetColor(255, 255, 255));

	return true;
}
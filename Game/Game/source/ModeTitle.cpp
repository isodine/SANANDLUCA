#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeTitle.h"
//#include "ModeGame.h"
#include "ModeStage0.h"

ModeTitle::ModeTitle() {
	titleHandle = LoadGraph("res/title.png");
}

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }
	
}

bool ModeTitle::Terminate() {
	base::Terminate();

	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg = (Key ^ keyold) & Key;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	int checkKey = GetJoypadInputState(DX_INPUT_KEY);

	if (Trg & PAD_INPUT_5) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render() {
	//DrawString(320, 240, "�^�C�g�����", GetColor(255, 255, 255));

	DrawGraph(0, 0, titleHandle, true);
	return true;
}
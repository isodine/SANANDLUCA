#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeTitle.h"
//#include "ModeGame.h"
#include "ModeStage0.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeTitle::Terminate() {
	base::Terminate();

	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_PAD1);
	Trg = (Key ^ keyold) & Key;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	if (Trg & PAD_INPUT_5) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	}

	return true;
}

bool ModeTitle::Render() {
	DrawString(320, 240, "�^�C�g�����", GetColor(255, 255, 255));

	return true;
}
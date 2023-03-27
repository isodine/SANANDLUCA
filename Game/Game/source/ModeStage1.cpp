#include "AppFrame.h"
#include "ModeStage1.h"
#include "ModeGameOver.h"

bool ModeStage1::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeStage1::Terminate() {
	base::Terminate();

	return true;
}

bool ModeStage1::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage2(), 1, "stage2");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(2), 1, "GameOver");
	}

	return true;
}

bool ModeStage1::Render() {
	DrawString(0, 0, "ステージ1", GetColor(255, 255, 255));

	return true;
}
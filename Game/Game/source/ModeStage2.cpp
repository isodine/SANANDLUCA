#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeStage2.h"
#include "ModeStage3.h"
#include "ModeGameOver.h"

bool ModeStage2::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeStage2::Terminate() {
	base::Terminate();

	return true;
}

bool ModeStage2::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage3(), 1, "stage3");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(4), 1, "GameOver");
	}

	return true;
}

bool ModeStage2::Render() {
	DrawString(0, 0, "ステージ2", GetColor(255, 255, 255));

	return true;
}
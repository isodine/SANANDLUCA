#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeStage0.h"
#include "ModeStage1.h"
#include "ModeGameOver.h"

bool ModeStage0::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeStage0::Terminate() {
	base::Terminate();

	return true;
}

bool ModeStage0::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage1(), 1, "stage1");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "GameOver");
	}

	return true;
}

bool ModeStage0::Render() {
	DrawString(0, 0, "チュートリアルステージ", GetColor(255, 255, 255));

	return true;
}
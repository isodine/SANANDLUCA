#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTitle.h"
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

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage0(), 1, "stage0");
	}

	return true;
}

bool ModeTitle::Render() {
	DrawString(0, 0, "ƒ^ƒCƒgƒ‹", GetColor(255, 255, 255));

	return true;
}
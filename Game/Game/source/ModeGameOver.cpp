#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGameOver.h"
#include "ModeStage1.h"
#include "ModeStage2.h"
#include "ModeStage3.h"
#include "ModeBoss.h"
#include "ModeTitle.h"


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

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}
	return true;
}

bool ModeGameOver::Render() {
	DrawString(0, 0, "ゲームオーバー", GetColor(255, 255, 255));

	return true;
}
#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeStage3.h"
#include "ModeBoss.h"
#include "ModeGameOver.h"

bool ModeStage3::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeStage3::Terminate() {
	base::Terminate();

	return true;
}

bool ModeStage3::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeBoss(), 1, "boss");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(5, false), 1, "GameOver");
	}

	return true;
}

bool ModeStage3::Render() {
	DrawString(0, 0, "ステージ3", GetColor(255, 255, 255));

	return true;
}
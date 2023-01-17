#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeBoss.h"
#include "ModeEnding.h"
#include "ModeGameOver.h"

bool ModeBoss::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeBoss::Terminate() {
	base::Terminate();

	return true;
}

bool ModeBoss::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeEnding(), 1, "ending");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "GameOver");
	}

	return true;
}

bool ModeBoss::Render() {
	DrawString(0, 0, "É{ÉX", GetColor(255, 255, 255));

	return true;
}
#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeLogo.h"
#include "ModeTitle.h"

bool ModeLogo::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeLogo::Terminate() {
	base::Terminate();

	return true;
}

bool ModeLogo::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeLogo::Render() {
	DrawString(0, 0, "ƒ`[ƒ€ƒƒS", GetColor(255, 255, 255));

	return true;
}
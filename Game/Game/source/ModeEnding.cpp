#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeEnding.h"
#include "ModeTitle.h"

bool ModeEnding::Initialize() {
	if (!base::Initialize()) { return false; }

	return true;
}

bool ModeEnding::Terminate() {
	base::Terminate();

	return true;
}

bool ModeEnding::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	}

	return true;
}

bool ModeEnding::Render() {
	DrawString(0, 0, "エンディング", GetColor(255, 255, 255));

	return true;
}
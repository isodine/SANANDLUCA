#include "AppFrame.h"
#include "ModeTitle.h"
#include "ModeStage0.h"
#include "ModeRule.h"


ModeTitle::ModeTitle() {
	titleHandle = LoadGraph("res/01_Tittle/Tittle.png");
	titlelogohandle = LoadGraph("res/01_Tittle/logo.png");
	pushlogo = LoadGraph("res/01_Tittle/text.png");
	SEcrik = LoadSoundMem("res/06_Sound/03_SE/決定ボタンを押す24.mp3");

	//VOICE用
	modeStart = false;
}

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

	if (!modeStart)
	{
		PlaySoundMem(VOICEtitle[GetRand(2)], DX_PLAYTYPE_BACK, true);
		modeStart = true;
	}
	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg = (Key ^ keyold) & Key;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）

	int checkKey = PAD_INPUT_1 | PAD_INPUT_2 | PAD_INPUT_3 | PAD_INPUT_4 | PAD_INPUT_5 | PAD_INPUT_6 | PAD_INPUT_7 | PAD_INPUT_8 | PAD_INPUT_9 | PAD_INPUT_10;


	if (Trg & checkKey) {
		PlaySoundMem(SEcrik, DX_PLAYTYPE_BACK, true);
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeRule(), 1, "Rule");
	}

	return true;
}

bool ModeTitle::Render() {
	DrawGraph(0, 0, titleHandle, true);
	DrawGraph(410, 0, titlelogohandle, true);
	DrawGraph(617, 812, pushlogo, true);
	return true;
}
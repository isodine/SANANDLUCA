#pragma once
#include "appframe.h"

class ModeTitle : public ModeBase {
	typedef ModeBase base;
public:
	ModeTitle();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	
	int titleHandle;//タイトルのハンドル
	int titlelogohandle;//タイトルロゴのハンドル
	int pushlogo;//プッシュUIのハンドル
	int SEcrik;//決定BGMのハンドル

	//VOICE用
	bool modeStart = false;
	int VOICEtitle[3] = { LoadSoundMem("res/06_Sound/02_Voice/00_Out_Game/01_TitleCall/San_Title_Call_Voice_01.wav") ,
						           LoadSoundMem("res/06_Sound/02_Voice/00_Out_Game/01_TitleCall/Lka_Title_Call_Voice_01.wav") ,
						           LoadSoundMem("res/06_Sound/02_Voice/00_Out_Game/01_TitleCall/SanLka_Title_Call_Voice_01.wav") };
};
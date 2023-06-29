#pragma once
#pragma once
#include "appframe.h"

class ModeRule : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	void ChangeMode();
private:
	int Rulehandle[5];//ルールのハンドル
	int pushbutton;//ボタンが押された回数
};
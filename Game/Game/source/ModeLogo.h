#pragma once
#include "appframe.h"

class ModeLogo : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	void ChangeMode();
private:
	int logohandle;//���S�̃n���h��
	int teamlogohandle;//�`�[�����S�̃n���h��
};
#pragma once
#include "appframe.h"
#include "Boss.h"

class ModeBoss : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void Walk();
	void Target();
	void Rush();
	void Crush();
	void Capture();
	void Down();

	VECTOR TargetPos;  //�^�[�Q�b�g�̃|�W�V����
	VECTOR TargetDir;  //�^�[�Q�b�g�̌���
	int SanLka;  //�T���ƃ��J�̂ǂ�����^�[�Q�b�g�ɂ��邩
	int WalkCount;  //�����Ēǂ���������


protected:
	Boss boss;
	SAN* san;
	LKA* lka;
};
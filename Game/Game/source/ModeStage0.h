#pragma once
#include "appframe.h"

class ModeStage0 : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	int handle;
	int Mattach_index;
	// 3D���f���`��p
	float Mtotal_time;
	float Mplay_time;
	VECTOR _vPos;	// �ʒu
	VECTOR _vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j
};
#pragma once
#include "AppFrame.h"
#include <string>

class SANclass;
class LKAclass;

class Enemy {
public:
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	void Slime(VECTOR SanPos, VECTOR LkaPos, int Handle, float speed);
	void Spider(VECTOR SanPos, VECTOR LkaPos, VECTOR SpiderPos, int Handle, float speed);
	void Boss(VECTOR SanPos, VECTOR LkaPos, VECTOR BossPos, int Handle, float speed);

	void SlimeRender(VECTOR Pos, int Handle);
	void SpiderRender(VECTOR Pos, int Handle);
	void BossRender(VECTOR Pos, int Handle);

	float sanDistance;
	float lkaDistance;

	int AttachAnim;
	float TotalTime;
	float PlayTime;

	VECTOR slimeDir;

	VECTOR sanPos;
	VECTOR lkaPos;
	VECTOR slimePos;

protected:
	enum class STATUS {
		NONE,
		ATTACK,
		HIT,
		WALK_KAI,
		_EOT_
	};
	STATUS _status;



};
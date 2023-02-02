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

	void Slime(VECTOR SanPos, VECTOR LkaPos, int Handle, int HandleMap, float speed);
	void Spider(VECTOR SanPos, VECTOR LkaPos, VECTOR SpiderPos, int Handle, float speed);
	void Boss(VECTOR SanPos, VECTOR LkaPos, VECTOR BossPos, int Handle, float speed);

	void SlimeJump();

	void SlimeRender(VECTOR Pos, int Handle);
	void SpiderRender(VECTOR Pos, int Handle);
	void BossRender(VECTOR Pos, int Handle);

	float sanDistance;
	float lkaDistance;
	float height;
	float slimecount;
	bool slimeSerch;
	bool slimeAttackFlag;

	int AttachAnim;
	float TotalTime;
	float PlayTime;

	MATRIX _rotationMatrix;

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
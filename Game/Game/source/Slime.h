#pragma once
#include "AppFrame.h"
#include <string>

class SANclass;
class LKAclass;

class Slime {
public:
	void Initialize(float x, float y, float z, int pH);
	void Terminate();
	void Process(VECTOR SanPos, VECTOR LkaPos, int HandleMap, float speed);
	void Render(VECTOR Pos);

	void SlimeU(VECTOR SanPos, VECTOR LkaPos, int HandleMap, float speed);

	void SlimeJump();

	void SlimeRender(VECTOR Pos);

	float sanDistance;
	float lkaDistance;
	float height;
	float slimecount;
	bool slimeSerch;
	bool slimeAttackFlag;
	bool slimeHitFlag;


	int AttachAnim;
	float TotalTime;
	float PlayTime;

	int slimeHandle;

	MATRIX _rotationMatrix;

	VECTOR slimeDir;
	VECTOR oldPos;

	VECTOR sanPos;
	VECTOR lkaPos;
	VECTOR slimePos;

	int mypH = 0;     //ÇPÅÅé_ê´ÅAÇQÅÅÉAÉãÉJÉäê´

	//std::vector<std::unique_ptr<Slime>> slime;

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
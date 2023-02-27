#pragma once
#include "appframe.h"
#include "Boss.h"

class SAN;
class LKA;

class ModeBoss : public ModeBase {
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	VECTOR TargetPos;  //ターゲットのポジション
	VECTOR TargetDir;  //ターゲットの向き
	int SanLka;  //サンとルカのどちらをターゲットにするか
	int WalkCount;  //歩いて追いかけた回数

	int StageHandle;
	int frameMapCollisionwall;
	int frameMapCollisionfloor;
	
	VECTOR	_vPos;					// 位置
	VECTOR	_vTarget;				// 距離
	float	_clipNear, _clipFar;	// クリップ

protected:
	Boss boss;
	SAN san;
	LKA lka;
	Camera _cam;
	SanBomb sanbomb;
	Damage damage;
};
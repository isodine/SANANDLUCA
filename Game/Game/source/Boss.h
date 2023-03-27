#pragma once

#include "appframe.h"
#include "BossSwamp.h"
#include "Damage.h"

class ModeBoss;
class SAN;
class LKA;
class SanBomb;
class LkaBomb;

class Boss {
public:
	void Initialize();
	void Terminate();
	void Process(Damage& damage);
	void Render();

	void Targeting(VECTOR sanPos, VECTOR lkaPos);
	void Rush(VECTOR sanPos, VECTOR lkaPos, int SanHandle, int LkaHandle, int MapHandle);
	void Capture();
	void CaptureEnd();
	void Rotation(VECTOR sanPos, VECTOR lkaPos);
	void Walk();
	void Crush();		//壁衝突時処理
	void Search();
	void Down();
	void Idle();
	void Pull();
	void SwampSpawn(bool IsSan);

	int Target;
	VECTOR BossPos;
	VECTOR BossSetDir;
	VECTOR BossDir;
	VECTOR RightHandPos;
	VECTOR LeftHandPos;
	VECTOR HandPos;
	VECTOR AddPos;
	VECTOR TargetDir;
	VECTOR SphereCenter;
	VECTOR BossPosition0;
	VECTOR BossPosition1;
	VECTOR BossPosition2;
	VECTOR BossPosition3;
	//VECTOR SwampPos;
	int handleBaseSan;
	int handleBaseLka;
	VECTOR swampDir;
	VECTOR swampDegreeDir;
	int SwampCnt;

	MATRIX rotationMatrix;
	VECTOR forward;

	enum class BOSSTYPE {
		NONE,
		RUSH,
		CAPTURE,
		CAPTUREEND,
		ROTATION,
		WALK,
		CRUSH,
		SEARCH,
		PULL,
		DOWN,
		IDLE,
	};

	BOSSTYPE type;

	enum class PH {
		ACID,
		ALCALI,
		NONE,
	};

	PH phType;
	PH oldphType;
	
	int RotateCount;//回転する時間
	int WaitCount;//ため攻撃のモーションのカウント
	int PullCount;//抜けるまでの秒数
	int CrushCount;//じたばたする時間
	int IdleCount;//休憩する時間
	int CaptureCount;//捕まえている時間
	int EndCount;//捕まえた後の時間
	int DownCount;//やられた時の時間
	int BossHP;//ボスの体力
	float PlayTime;
	int randomNum;
	int walkRand;
	int walkTimeCount;

	float StopDir;//回転が止まる誤差
	float StopPos;//止まる場所の誤差
	float rotate;//回転する速度

	bool rotateFlag;//TRUEなら回転する
	bool walkFlag;//TRUEなら歩く
	bool rushFlag;//TRUEなら攻撃準備から攻撃に移る
	bool targetFlag;//TRUEなら攻撃のターゲットを決める
	bool target;//TRUEならサンに攻撃
	bool idleFlag;//TRUEならアイドルモーション
	bool SanCatchFlag;//TRUEならサンを捕まえた
	bool LkaCatchFlag;//TRUEならルカを捕まえた
	bool crushFlag;//TRUEならTYPEをCrashにする
	bool AttackedFlag;//TRUEなら攻撃された
	bool searchFlag;//TRUEなら定位置を決める
	bool downFlag;//TRUEならやられた
	bool sanhitEf;//TRUEならダメージエフェクト出現
	bool lkahitEf;//TRUEならダメージエフェクト出現
	bool bosshitEf;//TRUEならダメージエフェクト出現
	bool bossdownEf;//TRUEならダウンエフェクト出現

	int acidHandle;//酸性のときのテクスチャ
	int alcaliHandle;//アルカリ性のときのテクスチャ
	int noneHandle;//中性の時のテクスチャ

	int Key1P;
	int Trg1P;
	int key;
	int trg;

	SAN* san;
	LKA* lka;
	SanBomb* sanB;
	LkaBomb* lkaB;
	ModeBoss* modeboss;
	modelInf model;
	modelManager* manager;
	BossSwamp Bswamp;
	std::vector<std::unique_ptr<BossSwamp>> swamps;
};
#pragma once
#include "AppFrame.h"
#include "SANclass.h"
#include "LKAclass.h"
#include <string>

class SAN;
class LKA;

class Gimmick {
public:
	Gimmick();
	void Initialize();
	void Terminate();
	void Process();
	void Render();
	void UpdateCollision();

	void SetSanLka(SAN* San, LKA* Lka) {
		san = San;
		lka = Lka;
	}
	float GetPolyMaxY(MV1_COLL_RESULT_POLY* Dim, int num);
	void Balance(VECTOR SanPos, VECTOR LkaPos);

	bool GetSanHitFlag() { return SanHitFlag; }
	bool GetLkaHitFlag() { return LkaHitFlag; }
	bool EnumFlag;  //天秤のステータスが変わったかどうか

	int BalanceHandle;

	int AttachAnim1;
	int AttachAnimSAN;
	int AttachAnimLKA;

	VECTOR SANDisk;
	VECTOR LKADisk;

	float PlayBalance;
	float TotalBalance;
	float BlendRate;
	float nowBlendRate;
	float BalancePer;//傾きの値。サンの時－1、ルカの時１

	bool SanHitFlag;
	bool LkaHitFlag;
	bool BalanceFlag;

	

	enum class BALANCE {
		EQUAL,
		SAN,
		LKA,
		NONE
	};

	enum class San {
		NONE,
		WAIT,
		WALK,
		JUMP,
		DAMAGE,
		CHARGE,
		ATTACK,
		DOWN,
		_EOT_
	};

	San San;

	enum class Lka {
		NONE,
		WAIT,
		WALK,
		JUMP,
		DAMAGE,
		CHARGE,
		ATTACK,
		DOWN,
		_EOT_
	};

	Lka Lka;

	BALANCE balance;
	BALANCE OldBalance;
private:
	SAN* san;
	LKA* lka;
	//Player* player;
};
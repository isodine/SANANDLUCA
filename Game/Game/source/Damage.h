#pragma once
#include "SANclass.h"
#include "LKAclass.h"



class Damage{
public:
	Damage();
	~Damage();
	virtual void Initialize(SAN* san, LKA* lka);
	virtual void Terminate();
	virtual void Process();
	virtual void Render();

	int SanHP;
	int LkaHP;

	float SanCoolTime;
	float LkaCoolTime;

	bool SanHitFlag;
	bool LkaHitFlag;

	float Distance;

	int SanOldtime;
	int LkaOldTime;
	float SanTime;
	float LkaTime;

protected:
	SAN* San;
	LKA* Lka;
};
#pragma once
#include "SANclass.h"
#include "LKAclass.h"

class Include;

class Damage{
public:
	Damage(Include& include);
	~Damage();
	virtual void Initialize(SAN* san, LKA* lka);
	virtual void Terminate();
	virtual void Process();
	virtual void Render();
	void DamageFloor();

	int SanHP;
	int LkaHP;

	float SanCoolTime;
	float LkaCoolTime;

	bool SanHitFlag;
	bool LkaHitFlag;

	float Distance;

protected:
	SAN* San;
	LKA* Lka;
	Include& _include;
};
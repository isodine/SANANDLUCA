#pragma once
#include "SANclass.h"
#include "LKAclass.h"

class Damage{
public:
	Damage();
	~Damage();
	virtual void Initialize();
	virtual void Terminate();
	virtual void Process();
	virtual void Render();

	int SanHP;
	int LkaHP;

	bool SanHitFlag;
	bool LkaHitFlag;

	float Distance;

protected:
	SAN San;
	LKA Lka;
};
#pragma once

class SAN;
class LKA;

class Damage{
public:
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
	SAN& san;
	LKA& lka;
};
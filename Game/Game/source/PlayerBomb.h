#pragma once

class PlayerBomb
{
public:
	PlayerBomb();
	~PlayerBomb();
	void BombReset();
	void SetSan(SAN& San);
	void SetLka(LKA& Lka);
	enum BombType
	{
		San,
		Lka
	};
	BombType mypH;

	VECTOR vPos;	// ˆÊ’u
	VECTOR vDir;	// Œü‚«

	float count = 0.f;
	float decrement = 10.f;

	float sphereSize = 0.f;
	float sphereMax = 50.f;

	bool bomblive = false;
	bool firstdir = false;

	enum Situation
	{
		None,
		Pop,
		Keep,
		Throw
	};
	Situation situation;

	SAN san;
	LKA lka;
};

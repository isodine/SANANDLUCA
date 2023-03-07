#pragma once
#include"Player.h"
#include "Gimmick.h"
#include "Boss.h"

class Boss;

class LKA:public Player, public Gimmick
{
public:
	LKA();
	~LKA();
	void Initialize() override;
	void Update(Damage& damage);
	void Render(Damage& damage);
	void Input() override;
	//void Jump();
	//void freeFall();

	int hpgaugehandle[6];
	int hphandle[6];
	float oldcount;
};
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
	void Update(Damage& damage, std::vector<std::unique_ptr<IronDoor>>* irondoors);
	void Render(Damage& damage);
	void Input() override;

	int hpgaugehandle[6];
	int hphandle;
	float oldcount;
	bool lkahitflag;
};
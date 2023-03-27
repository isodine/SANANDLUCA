#pragma once
#include"Player.h"
#include "Boss.h"

class SanBomb;
class Damage;
class Boss;

class SAN :public Player
{
public:
	SAN();
	~SAN();
	void Initialize() override;
	void Update(Damage& damage);
	void Render(Damage& damage);
	void Input() override;

private:
	int  sangauge;
	int  sanicon;
	int  sanframememori;
	int  sanfrask;
	int HPgauge = 0;

	int hpgaugehandle[6];
	int hphandle[6];
	float oldcount;
	bool _isflag;
};
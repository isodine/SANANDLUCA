#pragma once
#include"Player.h"
#include "Boss.h"

class Sanbomb;
class Damage;
class Boss;

class SAN :public Player
{
public:
	SAN();
	~SAN();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Input() override;
	//void Jump();
	//void freeFall();



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
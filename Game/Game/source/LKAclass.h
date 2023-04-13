#pragma once
#include"Player.h"
#include "Gimmick.h"
#include "Boss.h"

class Boss;
class SAN;

class LKA:public Player, public Gimmick
{
public:
	LKA();
	~LKA();
	void Initialize() override;
	void Update(Damage& damage, std::vector<std::unique_ptr<IronDoor>>* irondoors);
	void Render(Damage& damage);
	void Input() override;
	void Terminate() override;
	void KnockBack() override;
	void SetSan(SAN* _san);
	bool lkaBackFlag;


private:
	int hpgaugehandle[6];
	int hphandle;
	float oldcount;

	SAN* san;
};
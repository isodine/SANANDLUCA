#pragma once
#include"Player.h"

class LKA:public Player
{
public:
	LKA();
	~LKA();
	void Initialize()override;
	void Update(Camera& cam, Damage& damage);
	void Render(Damage& damage);
	void Input();

	int hpgaugehandle[6];
	int hphandle[6];
	float oldcount;
};
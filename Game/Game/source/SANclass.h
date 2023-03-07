#pragma once
#include"Player.h"

class SAN:public Player
{
public:
	SAN();
	~SAN();
	void Initialize()override;
	void Update(Camera& cam,Damage& damage);
	void Render(Damage& damage);
	void Input();

	int hpgaugehandle[6];
	int hphandle[6];
	float oldcount;
	bool _isflag;
};
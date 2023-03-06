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

	int hphandle[2];
	float oldcount;
	bool hpootd;
	bool _isflag;
};
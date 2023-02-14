#pragma once
#include"Player.h"

class SanBomb;
class Damage;

class SAN :public Player
{
public:
	SAN();
	~SAN();
	void Initialize();
	void Update(Camera& cam, SanBomb& sanB);
	void Render(SanBomb& sanB, Damage& damage);
	void Input();
	void Jump(Camera& cam);
	void freeFall(Camera& cam);



private:
	int  sangauge;
	int  sanicon;
	int  sanframememori;
	int  sanfrask;
	int HPgauge = 0;

};
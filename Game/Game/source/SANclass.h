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
	void Update() override;
	void Render() override;
	void Input() override;
	void Jump();
	void freeFall();



private:
	int  sangauge;
	int  sanicon;
	int  sanframememori;
	int  sanfrask;
	int HPgauge = 0;

};
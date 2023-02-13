#pragma once
class PlayerBomb
{
public:
	PlayerBomb();
	~PlayerBomb();

	enum BombType
	{
		San,
		Lka
	};
	BombType mypH;

	// 3Dƒ‚ƒfƒ‹•`‰æ—p
	//int Mhandle;
	//int Mattach_index;
	//float Mtotal_time;
	//float Mplay_time;

	VECTOR vPos;	// ˆÊ’u
	VECTOR vDir;	// Œü‚«

	enum Situation
	{
		Pop,
		Keep,
		Throw
	};
	Situation situation;

};

PlayerBomb::PlayerBomb()
{
}

PlayerBomb::~PlayerBomb()
{
}
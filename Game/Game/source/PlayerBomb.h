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

	// 3D���f���`��p
	//int Mhandle;
	//int Mattach_index;
	//float Mtotal_time;
	//float Mplay_time;

	VECTOR vPos;	// �ʒu
	VECTOR vDir;	// ����

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
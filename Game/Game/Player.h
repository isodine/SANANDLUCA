#pragma once
#include "appframe.h"

class Player
{
public:
	Player();
	~Player();
	virtual void Initialize();
	virtual void Update();
	virtual void Render();

public:
	enum Type
	{
		SAN,
		LKA
	};
	Type mypH;

	// 3D���f���`��p
	int Mhandle;
	int Mattach_index;
	float Mtotal_time;
	float Mplay_time;

	int HP;
	VECTOR myPos;
};
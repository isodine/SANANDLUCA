#pragma once
#include"SANclass.h"
#include"LKAclass.h"
#include "Player.h"
#include "Gimmick.h"

class Include {
public:
	SAN GetSan() { return san; }
	LKA GetLka() { return lka; }
	Player GetPlayer() { return player; }
	Gimmick GetGimmick() { return gimmick; }

protected:
	SAN san;
	LKA lka;
	Player player;
	Gimmick gimmick;
};

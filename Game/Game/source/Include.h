#pragma once
#include"SANclass.h"
#include"LKAclass.h"
#include "Player.h"

class Include {
public:
	SAN GetSan() { return san; }
	LKA GetLka() { return lka; }
	Player GetPlayer() { return player; }

protected:
	SAN san;
	LKA lka;
	Player player;
};

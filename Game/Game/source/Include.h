#pragma once
#include"SANclass.h"
#include"LKAclass.h"
#include "Player.h"
#include "ModeGame.h"

class Include {
public:
	SAN GetSan() { return san; }
	LKA GetLka() { return lka; }
	Player GetPlayer() { return player; }
	ModeGame GetModeGame() { return modegame; }

protected:
	SAN san;
	LKA lka;
	Player player;
	ModeGame modegame;
};

#pragma once
#include "SANclass.h"
#include "LKAclass.h"
#include "Slime.h"

class ModeGame;

class Damage {
public:
	Damage();
	~Damage();
	virtual void Initialize(SAN* san, LKA* lka);
	virtual void Terminate();
	virtual void Process();
	virtual void SlimeDamage(std::vector<std::unique_ptr<Slime>>& slimes);
	virtual void Render();
	void SetGame(ModeGame* game);

	int MaxSanHP,SanHP;
	int MaxLkaHP,LkaHP;

	float SanCoolTime;
	float LkaCoolTime;

	bool SanHitFlag;
	bool LkaHitFlag;

	bool stageFlag;//trueの時にダメージ床の判定がONになる

	float Distance;

	int stageHandle;

	//VOICE用
	int VOICEdamageSAN[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_01.wav"),
	                          LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_02.wav") };
	int VOICEdamageLKA[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_01.wav"),
							  LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_02.wav") };

protected:
	SAN* San;
	LKA* Lka;
	ModeGame* Game;
};
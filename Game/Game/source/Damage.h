#pragma once
#include "SANclass.h"
#include "LKAclass.h"
#include "Slime.h"

class SAN;
class LKA;
class ModeGame;
class SanBomb;
class LkaBomb;

class Damage {
	
public:
	Damage();
	~Damage();

	virtual void SwampColl(std::vector<std::unique_ptr<BossSwamp>>& swamps);
	//void SetGame(ModeGame* game);
	void Initialize(SAN* san, LKA* lka);
	void Terminate();
	void Process();
	void StageDamage(int StageHandle);
	void SlimeDamage(std::vector<std::unique_ptr<Slime>>& slimes);
	void Render();
	void SetBomb(SanBomb* sanbomb, LkaBomb* lkabomb);

	MV1_COLL_RESULT_POLY_DIM HitPolySan;
	MV1_COLL_RESULT_POLY_DIM HitPolyLka;

	float SanCoolTime;//サンがダメージを受けた時のクールタイム
	float LkaCoolTime;//ルカがダメージを受けた時のクールタイム

	bool SanHitFlag;//TRUEならサンがダメージを受けるものに触れた
	bool LkaHitFlag;//TRUEならルカがダメージを受けるものに触れた
	bool stageFlag;//trueの時にダメージ床の判定がONになる

	float Distance;

	int stageHandle;

	MV1_COLL_RESULT_POLY_DIM HitPolySanBomb;
	MV1_COLL_RESULT_POLY_DIM HitPolyLkaBomb;
	//VOICE用
	int VOICEdamageSAN[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_01.wav"),
	                          LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_02.wav") };
	int VOICEdamageLKA[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_01.wav"),
							  LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_02.wav") };

protected:
	SAN* San;
	LKA* Lka;
	ModeGame* Game;
	SanBomb* Sanbomb;
	LkaBomb* Lkabomb;
};
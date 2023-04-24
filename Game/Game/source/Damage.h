/*****************************************************************//**
 * \file   Damage.h
 * \brief  プレイヤーのダメージ判定全般
 *
 * \author 土屋　涼乃
 * \date   January 2023
 *********************************************************************/
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

	virtual void SwampColl(std::vector<std::unique_ptr<BossSwamp>>& swamps);//ボスが出した沼とのダメージ判定
	void Initialize(SAN* san, LKA* lka);
	void Terminate();
	void Process();
	void StageDamage(int StageHandle);//ステージにある沼とのダメージ判定
	void SlimeDamage(std::vector<std::unique_ptr<Slime>>& slimes);//スライムとのダメージ判定
	void Render();
	void SetBomb(SanBomb* sanbomb, LkaBomb* lkabomb);

	MV1_COLL_RESULT_POLY_DIM HitPolySan;//ステージとサン（１P）との当たり判定
	MV1_COLL_RESULT_POLY_DIM HitPolyLka;//ステージとルカ（２P）との当たり判定

	float SanCoolTime;//サンがダメージを受けた時のクールタイム
	float LkaCoolTime;//ルカがダメージを受けた時のクールタイム

	bool SanHitFlag;//TRUEならサンがルカかルカのボムに触れた
	bool LkaHitFlag;//TRUEならルカがサンかサンのボムに触れた
	bool SanFloorHitFlag;//TRUEならサンがダメージ床に触れた
	bool LkaFloorHitFlag;//TRUEならルカがダメージ床に触れた
	bool SanSlimeHitFlag;//TRUEならサンがスライムに触れた
	bool LkaSlimeHitFlag;//TRUEならルカがスライムに触れた
	bool stageFlag;//trueの時にダメージ床の判定がONになる

	float Distance;//プレイヤー同士の距離

	MV1_COLL_RESULT_POLY_DIM HitPolySanBomb;//サン（１P）のボムとルカ（２P）との当たり判定
	MV1_COLL_RESULT_POLY_DIM HitPolyLkaBomb;//ルカ（２P）のボムとサン（１P）との当たり判定
	//VOICE用
	int VOICEdamageSAN[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_01.wav"),
	                          LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_02.wav") };//サン（１P）のダメージボイス
	int VOICEdamageLKA[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_01.wav"),
							  LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_02.wav") };//ルカ（２P）のダメージボイス

protected:
	SAN* San;
	LKA* Lka;
	ModeGame* Game;
	SanBomb* Sanbomb;
	LkaBomb* Lkabomb;
};
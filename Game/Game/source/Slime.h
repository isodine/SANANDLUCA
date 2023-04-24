/*****************************************************************//**
 * \file   Slime.h
 * \brief  スライムの動作全般
 * 
 * \author 土屋　涼乃
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
#include <string>

class SAN;
class LKA;
class SanBomb;
class LkaBomb;

class Slime {
public:
	void Initialize(float x, float y, float z, int pH);
	void Terminate();
	void Process(VECTOR SanPos, VECTOR LkaPos, int HandleMap, float speed, int mypH);
	void Render(int pH);
	void AcidWalk(float speed);//酸性スライムの巡回
	void AlkaliWalk(float speed);//アルカリ性スライムの巡回
	void SanTargeting(VECTOR SanPos, float speed);//アルカリ性スライムがサン（１P）を追いかける
	void LkaTargeting( VECTOR LkaPos, float speed);//酸性スライムがルカ（２P）を追いかける
	void AcidJump(VECTOR SanPos);//アルカリ性スライムがサン（１P）を攻撃する
	void AlkaliJump(VECTOR LkaPos);//酸性スライムがルカ（２P）を攻撃する

	void SetSan(SAN* san);
	void SetLka(LKA* lka);
	void SetSanBomb(SanBomb* sanbomb);
	void SetLkaBomb(LkaBomb* lkabomb);

	float sanDistance;//スライムとサンの距離
	float lkaDistance;//スライムとルカの距離
	float acidcount;//モーションのフレーム数
	float alkalicount;//モーションのフレーム数
	int slimeHP;//スライムのHP
	bool slimeAttackFlag;//TRUEなら攻撃に入る
	bool sanHitFlag;//TRUEならスライムがサンに当たった
	bool lkaHitFlag;//TRUEならルカに当たった

	int AttachAnim;
	float TotalTime;
	float PlayTime;

	int slimeHandle;//スライムのモデル
	int acidHandle;//酸性スライムのテクスチャ
	int alkaliHandle;//アルカリ性スライムのテクスチャ

	MV1_COLL_RESULT_POLY_DIM SANhitPolyDimAcid;//酸性スライムと酸性ボムとの当たり判定
	MV1_COLL_RESULT_POLY_DIM LKAhitPolyDimAlkali;//アルカリ性スライムとアルカリ性ボムとの当たり判定
	MV1_COLL_RESULT_POLY_DIM LKAhitPolyDimAcid;//酸性スライムとアルカリ性ボムとの当たり判定
	MV1_COLL_RESULT_POLY_DIM SANhitPolyDimAlkali;//アルカリ性スライムと酸性ボムとの当たり判定
	MV1_COLL_RESULT_POLY_DIM hitPolyDim1;//アルカリ性スライムとサン（１P）との当たり判定
	MV1_COLL_RESULT_POLY_DIM hitPolyDim2;//酸性スライムとルカ（２P）との当たり判定

	MATRIX _rotationMatrix;

	VECTOR slimeDir;//スライムの向き
	VECTOR oldPos;//スライムの前の場所

	VECTOR sanPos;//スライムから見たサンの向き
	VECTOR lkaPos;//スライムから見たルカの向き
	VECTOR slimePos;//スライムの場所

	VECTOR acidSlimePos;//酸性スライムの場所
	VECTOR alkaliSlimePos;//アルカリ性スライムの場所

	VECTOR forward;//スライムの進む向き
	VECTOR slimeTargetPos;//スライムが目指すポイント
	VECTOR acidPos[4];//酸性スライムが巡回するときに通過するポイント

	VECTOR alkaliPos[4];//アルカリ性スライムが巡回するときに通過するポイント

	int SearchPosMinX;//サンかルカがこの範囲に入ったらスライムが追いかける
	int SearchPosMaxX;
	int SearchPosMinZ;
	int SearchPosMaxZ;

	float slimeError;//スライムの座標の誤差
	int acidPassedCount;//酸性スライムが通過した数
	int alkaliPassedCount;//アルカリ性スライムが通過した数

	bool acidDieFlag;//TRUEなら酸性スライムが死ぬ
	bool alkaliDieFlag;//TRUEならアルカリ性スライムが死ぬ

	int mypH = 0;     //１＝酸性、２＝アルカリ性

	SAN* _san;
	LKA* _lka;
	SanBomb* _sanbomb;
	LkaBomb* _lkabomb;
protected:
	//スライムの状態
	enum class STATUS {
		NONE,
		ATTACK,
		HIT,
		WALK_KAI,
		_EOT_
	};
	STATUS _status;

	

};
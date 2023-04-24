/*****************************************************************//**
 * \file   Gimmick.h
 * \brief  天秤の動作全般
 *
 * \author 土屋　涼乃
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
#include "SANclass.h"
#include "LKAclass.h"
#include <string>

class SAN;
class LKA;

class Gimmick {
public:
	Gimmick();
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	void SetSanLka(SAN* San, LKA* Lka) {
		san = San;
		lka = Lka;
	}
	void Balance(VECTOR SanPos, VECTOR LkaPos);

	bool GetSanHitFlag() { return SanHitFlag; }
	bool GetLkaHitFlag() { return LkaHitFlag; }
	bool EnumFlag;  //天秤のステータスが変わったかどうか

	int BalanceHandle;//天秤のモデルのハンドル
	int AttachAnim1;//天秤の水平モーション
	int AttachAnimSAN;//天秤の赤い皿方向の傾きモーション
	int AttachAnimLKA;//天秤の青い皿方向の傾きモーション

	VECTOR SANDisk;//赤い皿の上の座標
	VECTOR LKADisk;//青い皿の上の座標

	float BlendRate;//モーションのブレンド率
	float BalancePer;//傾きの値。サンの時－1に近づく、ルカの時１に近づく

	bool SanHitFlag;//TRUEなら赤い皿に乗った
	bool LkaHitFlag;//TRUEなら青い皿に乗った
	bool BalanceFlag;//水平かどうかのフラグ

	
	//SANの時赤い皿の方に傾く
	//LKAの時青い皿の方に傾く
	//EQUALの時平行、もしくは平行になろうとしている
	enum class BALANCE {
		EQUAL,
		SAN,
		LKA,
		NONE
	};

	BALANCE balance;//天秤のタイプ
private:
	SAN* san;
	LKA* lka;
};
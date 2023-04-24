/*****************************************************************//**
 * \file   Boss.h
 * \brief  ボスの挙動全般
 * 
 * \author 土屋　涼乃
 * \date   February 2023
 *********************************************************************/

#pragma once

#include "appframe.h"
#include "BossSwamp.h"
#include "Damage.h"

class ModeBoss;
class SAN;
class LKA;
class SanBomb;
class LkaBomb;

class Boss {
public:
	void Initialize();
	void Terminate();
	void Process(Damage& damage);
	void Render();

	void Targeting(VECTOR sanPos, VECTOR lkaPos);//攻撃対象の決定、その方向へ向く
	void Rush(VECTOR sanPos, VECTOR lkaPos, int SanHandle, int LkaHandle, int MapHandle);//突進攻撃
	void Capture();//プレイヤーを捕まえて攻撃する
	void CaptureEnd();//捕まえていたプレイヤーを離す
	void Rotation(VECTOR sanPos, VECTOR lkaPos);//プレイヤーの方向を交互に向く
	void Walk();//指定された場所に歩いていく
	void Crush();//壁衝突時処理
	void Search();//移動する場所を決める
	void Down();//倒された時の処理
	void Idle();//休憩モーション再生
	void Pull();//壁から抜ける
	void SwampSpawn(bool IsSan);//壁に衝突したときタイプに応じた沼を生成する

	VECTOR BossSetDir;//ボスが向く予定の方向
	VECTOR BossDir;//ボスの向き
	VECTOR HandPos;//ボスのはさみの座標
	VECTOR AddPos;//ボスのはさみの中心に移動させるための座標
	VECTOR SphereCenter;//ボスのはさみの中にあるキャラや壁との当たり判定をとるための級の中心座標
	VECTOR BossPosition0;//BossPosition0からBossPosition3はボスが移動する場所
	VECTOR BossPosition1;
	VECTOR BossPosition2;
	VECTOR BossPosition3;
	int handleBaseSan;//酸性の沼のハンドル
	int handleBaseLka;//アルカリ性の沼のハンドル
	VECTOR swampDir;
	VECTOR swampDegreeDir;
	int SwampCnt;//沼を出す回数

	MATRIX rotationMatrix;//ボスの向きを出す行列
	VECTOR forward;//ボスの向き

	//ボスの状態
	enum class BOSSTYPE {
		NONE,
		RUSH,
		CAPTURE,
		CAPTUREEND,
		ROTATION,
		WALK,
		CRUSH,
		SEARCH,
		PULL,
		DOWN,
		IDLE,
	};

	BOSSTYPE type;

	//ボスのタイプ
	enum class PH {
		ACID,
		ALKALI,
		NONE,
	};

	PH phType;//ボスのタイプ
	PH oldphType;//ボスの前のタイプ
	
	int RotateCount;//回転する時間
	int WaitCount;//ため攻撃のモーションのカウント
	int PullCount;//抜けるまでの秒数
	int CrushCount;//じたばたする時間
	int IdleCount;//休憩する時間
	int CaptureCount;//捕まえている時間
	int EndCount;//捕まえた後の時間
	int DownCount;//やられた時の時間
	int BossHP;//ボスの体力
	int BossMaxHP;//ボスの最大体力
	int HPhandle;//ボスのHPの画像のハンドル
	int iconhandle;//ボスのアイコンのハンドル
	int BGhandle;//ボスのHP乃ベースのハンドル
	int flamehandle;//ボスHPフレームのハンドル

	int BossSuck;	//ボス吸引時SE
	int BossSearch; //ボス探知時SE
	bool BossSuckflag = false;//ボスの吸引サウンドを再生するために一度だけTRUEになるフラグ
	bool BossSearchflag = false;//ボスの探知サウンドを再生するために一度だけTRUEになるフラグ

	float StopDir;//回転が止まる誤差
	float StopPos;//止まる場所の誤差
	float rotate;//回転する速度

	bool rotateFlag;//TRUEなら回転する
	bool walkFlag;//TRUEなら歩く
	bool rushFlag;//TRUEなら攻撃準備から攻撃に移る
	bool targetFlag;//TRUEなら攻撃のターゲットを決める
	bool target;//TRUEならサンに攻撃
	bool idleFlag;//TRUEならアイドルモーション
	bool SanCatchFlag;//TRUEならサンを捕まえた
	bool LkaCatchFlag;//TRUEならルカを捕まえた
	bool crushFlag;//TRUEならTYPEをCrashにする
	bool AttackedFlag;//TRUEなら攻撃された
	bool searchFlag;//TRUEなら定位置を決める
	bool downFlag;//TRUEならやられた
	bool sanhitEf;//TRUEならダメージエフェクト出現
	bool lkahitEf;//TRUEならダメージエフェクト出現
	bool bosshitEf;//TRUEならダメージエフェクト出現
	bool bossdownEf;//TRUEならダウンエフェクト出現

	int acidHandle;//酸性のときのテクスチャ
	int alkaliHandle;//アルカリ性のときのテクスチャ
	int noneHandle;//中性の時のテクスチャ

	int Key1P;
	int Trg1P;
	int key;
	int trg;

	SAN* san;
	LKA* lka;
	SanBomb* sanB;
	LkaBomb* lkaB;
	ModeBoss* modeboss;
	modelInf model;
	modelManager* manager;
	BossSwamp Bswamp;
	std::vector<std::unique_ptr<BossSwamp>> swamps;
};
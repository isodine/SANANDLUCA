/**
 * @file IronDoor.h
 * @brief 鉄ドアのギミックを動かすプログラム
 * @author 磯島武尊
 * @date March 2023
 */

#pragma once
class IronDoor
{
public:
	IronDoor();
	~IronDoor();
	//初期化処理
	void Initialize(bool type, VECTOR Pos);
	//更新処理
	void Update(SanBomb& sanbomb, LkaBomb& lkabomb);
	//削除処理
	void Terminate();
	//描画処理
	void Render();
	//当たり判定処理
	void CollCheck(SAN& san, LKA& lka);

	// 3Dモデル描画用
	int handle;				//モデルデータ
	VECTOR vPos;			//位置
	int handleCol;			//モデルの当たり判定用変数
	int handleIronDoor;		//元モデル１
	int handleIronMeltDoor;	//元モデル２
	bool isSan = false;		//キャラクター識別用
	bool melt = false;		//モデル変化通知
};

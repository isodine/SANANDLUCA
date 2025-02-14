/**
 * @file LKAclass.h
 * @brief ルカ特有の動きを処理するプログラム
 * @author 磯島武尊
 * @date December 2022
 *
 * @note HPゲージ周りは	@author 田原魁人 ,	ノックバックは	@author 土屋涼乃
 */

#pragma once
#include"Player.h"
#include "Gimmick.h"
#include "Boss.h"

class Boss;
class SAN;

class LKA:public Player, public Gimmick
{
public:
	LKA();
	~LKA();
	//初期化処理
	void Initialize() override;
	//更新処理
	void Update(Damage& damage, std::vector<std::unique_ptr<IronDoor>>* irondoors);
	//描画処理
	void Render(Damage& damage);
	//操作取得
	void Input() override;
	//削除処理
	void Terminate() override;
	//ノックバック処理
	void KnockBack() override;
	void SetSan(SAN* _san);
	bool lkaBackFlag;


private:
	int hpgaugehandle[6];
	int hphandle;
	float oldcount;

	SAN* san;
};
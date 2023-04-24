#pragma once
#include"Player.h"
#include "Boss.h"

class SanBomb;
class Damage;
class Boss;
class LKA;

//サンのクラス
class SAN :public Player
{
public:
	SAN();
	~SAN();
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
	//ノックバック
	void KnockBack() override;
	void SetLka(LKA* _lka);
	bool sanBackFlag;


private:
	int  sangauge;
	int  sanicon;
	int  sanframememori;
	int  sanfrask;
	int HPgauge = 0;

	int hpgaugehandle[6];
	int hphandle;
	float oldcount;
	bool _isflag;

	LKA* lka;
};
#pragma once
#include "PlayerBomb.h"

class LkaBomb:public PlayerBomb
{
public:
	LkaBomb();
	~LkaBomb();
	void Initialize(LKA& lka);
	void Update(LKA& lka);
	void Terminate();
	void Render();
	void Throw(LKA& lka);
	void bombthrow();
	void BombReset();
	void Bombdead();
	void EffectReset();
private:
	int _effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int _playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;//再生時間管理
	int IsPlaying;//エフェクトが再生されているか
	bool Isbombdead;//ボムは生きているか

};
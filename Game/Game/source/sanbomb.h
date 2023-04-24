#pragma once
#include "PlayerBomb.h"

class SanBomb :public PlayerBomb
{
public:
	SanBomb();
	~SanBomb();
	void Initialize(SAN& san);
	void Update(SAN& san);
	void Render();
	void Move();
	void Throw(SAN& san);
	void Bombdead();
	void bombthrow();
	void EffectReset();
private:
	int _effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int _playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;//ボムのエフェクト再生時間管理
	int IsPlaying;//エフェクトは再生されているか
	bool Isbombdead;//ボムは生きているか
};
#pragma once
class SAN;
class LKA;
class Sancircle
{
public:
	Sancircle();
	~Sancircle();

	void Update(SAN& san,LKA& lka);
	void Render();
private:
	int	_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int	_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;
	int IsPlaying;//エフェクトが再生されているか

};
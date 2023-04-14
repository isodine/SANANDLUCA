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
	void EffectReset();
private:
	int	_effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int	_playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;
	bool Iscircle;
	float PlayTime = 0.0f;
	int _isEffect = 0;
	int IsPlaying = -1;
	int cautionHandle;

};
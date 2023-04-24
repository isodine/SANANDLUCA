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
	int oldcount;//サークルの再生時間管理
	bool Iscircle;//サークルは出現しているか
	int IsPlaying;//サークルは再生されているか


};
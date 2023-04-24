#pragma once
class LKA;
class SAN;
class Lkacircle
{
public:
	Lkacircle();
	~Lkacircle();

	void Init();
	void Update(SAN& san,LKA& lka);
	void Render();
	void EffectReset();
private:
	int		_effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;//ボムの再生時間管理
	bool Iscircle;//サークルが出現しているか
	int IsPlaying;//サークルは再生されているか


};
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
private:
	int		_effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;
	bool Iscircle;
	float PlayTime = 0.0f;
	int _isEffect = 0;
	int IsPlaying = -1;


};
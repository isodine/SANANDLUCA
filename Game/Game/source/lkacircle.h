#pragma once
class LKA;
class Lkacircle
{
public:
	Lkacircle();
	~Lkacircle();

	void Init();
	void Update(LKA& lka);
	void Render();
private:
	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;
	float PlayTime = 0.0f;
	int _isEffect = 0;
	int IsPlaying = -1;


};
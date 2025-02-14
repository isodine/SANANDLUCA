#pragma once
class Boss;
class Bossrun
{
public:
	Bossrun();
	~Bossrun();

	void Update(Boss& boss);
	void Render();
private:
	int	_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int	_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int IsPlaying;//エフェクトが再生されているか
	float runEfsize; //走るエフェクトのサイズ設定
};

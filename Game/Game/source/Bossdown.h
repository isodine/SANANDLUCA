#pragma once
class Boss;
class Bossdown
{
public:
	Bossdown();
	~Bossdown();

	void Update(Boss& boss);
	void Render();
private:
	int	_effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int	_playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int IsPlaying[2]; //エフェクトが再生されているか
	float downEfsize[2];//攻撃時エフェクトのサイズ設定
	bool Isdown;
};
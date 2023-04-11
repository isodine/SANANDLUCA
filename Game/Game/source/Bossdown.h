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
	int	_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int	_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int IsPlaying; //エフェクトが再生されているか
	float downEfsize;//攻撃時エフェクトのサイズ設定
	bool Isdown;
	int exprodesound;
	int biribirisound;
};
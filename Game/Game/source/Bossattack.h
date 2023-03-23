#pragma once
class Damage;
class Boss;
class Bossattack
{
public:
	Bossattack();
	~Bossattack();

	void Update(Boss& boss,Damage& damage);
	void Render(Boss& boss);
private:
	int	_effectResourceHandle[2];		// エフェクトファイルをロードするハンドル
	int	_playingEffectHandle[2];		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int IsPlaying; //エフェクトが再生されているか
	float attackEfsize;//攻撃時エフェクトのサイズ設定
};
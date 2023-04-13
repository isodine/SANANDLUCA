#pragma once
class Boss;
class Bossdamage
{
public:
	Bossdamage();
	~Bossdamage();

	void Update(Boss& boss);
	void Render(Boss& boss);

private:
	int	_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int	_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	float damageEfsize;//ダメージエフェクトのサイズ設定
};
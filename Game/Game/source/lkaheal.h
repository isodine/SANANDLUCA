#pragma once
#pragma once
class LKA;
class Lkaheal
{
public:
	Lkaheal();
	~Lkaheal();

	void Init();
	void Update(LKA& lka);
	void Render();
private:
	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;//エフェクトの再生時間管理
	int IsPlaying = -1;//再生されているか


};
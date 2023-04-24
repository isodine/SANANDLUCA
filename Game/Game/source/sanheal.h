#pragma once
class SAN;
class Sanheal
{
public:
	Sanheal();
	~Sanheal();

	void Init();
	void Update(SAN& san);
	void Render();
private:
	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;//エフェクトの再生時間管理
	int IsPlaying;//エフェクトが再生されているか

};
#pragma once
class SAN;
class Sanbomb
{
public:
	Sanbomb();
	~Sanbomb();

	void Init();
	void Update(SAN& san);
	void Render();
	void bombthrow();
private:
	int _effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int _playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;
	float PlayTime = 0.0f;
	int _isEffect = 0;
	int _isthrow = 0;
	int IsPlaying = -1;
	int _KeyEf, _TrgEf;
	float _hight, _throw;
	float _position_x, _position_y, _position_z;
};
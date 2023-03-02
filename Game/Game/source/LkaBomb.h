#pragma once
class LKA;
class Lkabomb
{
public:
	Lkabomb();
	~Lkabomb();

	void Init();
	void Update(LKA& lka);
	void Render();
	void bombthrow();
private:
	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	int oldcount;
	float PlayTime = 0.0f;
	int   _gKeyEf, _gTrgEf, _KeyEf, _TrgEf;
	int _isEffect = 0;
	float _throw;
	float _hight;
	int _isthrow = 0;

	// エフェクト位置
	float _position_x;
	float _position_y;
	float _position_z;


};
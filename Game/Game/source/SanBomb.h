#pragma once
#include "PlayerBomb.h"

class SanBomb :public PlayerBomb
{
public:
	SanBomb();
	~SanBomb();
	void Initialize(SAN& san);
	void Update(SAN& san);
	void Render();
	void Move();
	void Throw(SAN& san);
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
#pragma once
#include "PlayerBomb.h"

class SanBomb:public PlayerBomb
{
public:
	SanBomb();
	~SanBomb();
	void Initialize(SAN& san);
	void Update(SAN& san);
	void Render();
	void Move();
	void Throw(SAN& san);

private:
	int _effectResourceHandle;
	int _playingEffectHandle;
	int oldcount;
	int _isthrow;
	int _isEffect;
};

#pragma once
#include "PlayerBomb.h"

class LkaBomb:public PlayerBomb
{
public:
	LkaBomb();
	~LkaBomb();
	void Initialize(LKA& lka);
	void Update(LKA& lka);
	void Render();
	void Move();
	void Throw(LKA& lka);
	void bombthrow();
	void BombReset();
	void Bombdead();
private:
	int _effectResourceHandle[2];		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int _playingEffectHandle[2];		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;
	float PlayTime = 0.0f;
	int _isEffect = 0;
	int _isthrow = 0;
	int IsPlaying = -1;
	int _KeyEf, _TrgEf;
	float _hight, _throw;
	float _position_x,_position_y, _position_z;
	bool Isbombdead;

};
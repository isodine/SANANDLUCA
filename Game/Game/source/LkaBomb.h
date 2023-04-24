#pragma once
#include "PlayerBomb.h"

class LkaBomb:public PlayerBomb
{
public:
	LkaBomb();
	~LkaBomb();
	void Initialize(LKA& lka);
	void Update(LKA& lka);
	void Terminate();
	void Render();
	void Throw(LKA& lka);
	void bombthrow();
	void BombReset();
	void Bombdead();
	void EffectReset();
private:
	int _effectResourceHandle[2];		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int _playingEffectHandle[2];		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;//�Đ����ԊǗ�
	int IsPlaying;//�G�t�F�N�g���Đ�����Ă��邩
	bool Isbombdead;//�{���͐����Ă��邩

};
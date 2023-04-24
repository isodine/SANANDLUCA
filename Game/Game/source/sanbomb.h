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
	void Bombdead();
	void bombthrow();
	void EffectReset();
private:
	int _effectResourceHandle[2];		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int _playingEffectHandle[2];		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;//�{���̃G�t�F�N�g�Đ����ԊǗ�
	int IsPlaying;//�G�t�F�N�g�͍Đ�����Ă��邩
	bool Isbombdead;//�{���͐����Ă��邩
};
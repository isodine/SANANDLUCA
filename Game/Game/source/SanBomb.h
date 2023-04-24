#pragma once
#include "PlayerBomb.h"

//�T���̃{���̃N���X
class SanBomb :public PlayerBomb
{
public:
	SanBomb();
	~SanBomb();
	//����������
	void Initialize(SAN& san);
	//�X�V����
	void Update(SAN& san);
	//�폜����
	void Terminate();
	//�`�揈��
	void Render();
	//���̈ړ�����
	void Throw(SAN& san);
	//�{���̏���
	void Bombdead();

	void EffectReset();
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
	float _position_x, _position_y, _position_z;
	bool Isbombdead;					//�����ʒm
};
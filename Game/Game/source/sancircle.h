#pragma once
class SAN;
class LKA;
class Sancircle
{
public:
	Sancircle();
	~Sancircle();

	void Update(SAN& san,LKA& lka);
	void Render();
private:
	int	_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;
	int IsPlaying;//�G�t�F�N�g���Đ�����Ă��邩

};
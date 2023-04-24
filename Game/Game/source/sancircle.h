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
	void EffectReset();
private:
	int	_effectResourceHandle[2];		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle[2];		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;//�T�[�N���̍Đ����ԊǗ�
	bool Iscircle;//�T�[�N���͏o�����Ă��邩
	int IsPlaying;//�T�[�N���͍Đ�����Ă��邩


};
#pragma once
class Boss;
class Bossdown
{
public:
	Bossdown();
	~Bossdown();

	void Update(Boss& boss);
	void Render();
private:
	int	_effectResourceHandle[2];		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle[2];		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int IsPlaying[2]; //�G�t�F�N�g���Đ�����Ă��邩
	float downEfsize[2];//�U�����G�t�F�N�g�̃T�C�Y�ݒ�
	bool Isdown;
};
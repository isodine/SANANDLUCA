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
	int	_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int IsPlaying; //�G�t�F�N�g���Đ�����Ă��邩
	float downEfsize;//�U�����G�t�F�N�g�̃T�C�Y�ݒ�
	bool Isdown;
	int exprodesound;
	int biribirisound;
};
#pragma once
class Damage;
class Boss;
class Bossattack
{
public:
	Bossattack();
	~Bossattack();

	void Update(Boss& boss,Damage& damage);
	void Render(Boss& boss);
private:
	int	_effectResourceHandle[2];		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle[2];		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int IsPlaying; //�G�t�F�N�g���Đ�����Ă��邩
	float attackEfsize;//�U�����G�t�F�N�g�̃T�C�Y�ݒ�
};
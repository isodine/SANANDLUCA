#pragma once
class Boss;
class Bossdamage
{
public:
	Bossdamage();
	~Bossdamage();

	void Update(Boss& boss);
	void Render(Boss& boss);

private:
	int	_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int IsPlaying ;//�G�t�F�N�g���Đ�����Ă��邩
	float damageEfsize;//�_���[�W�G�t�F�N�g�̃T�C�Y�ݒ�
};
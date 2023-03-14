#pragma once
class Boss;
class Bossrun
{
public:
	Bossrun();
	~Bossrun();

	void Update(Boss& boss);
	void Render();
private:
	int	_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int IsPlaying = -1;
};

#pragma once
#pragma once
class LKA;
class Lkaheal
{
public:
	Lkaheal();
	~Lkaheal();

	void Init();
	void Update(LKA& lka);
	void Render();
private:
	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;//�G�t�F�N�g�̍Đ����ԊǗ�
	int IsPlaying = -1;//�Đ�����Ă��邩


};
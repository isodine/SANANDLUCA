#pragma once
class SAN;
class Sanheal
{
public:
	Sanheal();
	~Sanheal();

	void Init();
	void Update(SAN& san);
	void Render();
private:
	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;//�G�t�F�N�g�̍Đ����ԊǗ�
	int IsPlaying;//�G�t�F�N�g���Đ�����Ă��邩

};
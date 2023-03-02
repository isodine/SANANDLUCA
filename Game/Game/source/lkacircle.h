#pragma once
class LKA;
class Lkacircle
{
public:
	Lkacircle();
	~Lkacircle();

	void Init();
	void Update(LKA& lka);
	void Render();
private:
	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;
	float PlayTime = 0.0f;
	int _isEffect = 0;
	int IsPlaying = -1;


};
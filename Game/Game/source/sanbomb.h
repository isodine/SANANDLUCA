#pragma once
class SAN;
class Sanbomb
{
public:
	Sanbomb();
	~Sanbomb();

	void Init();
	void Update(SAN& san);
	void Render();
	void bombthrow();
private:
	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	int oldcount;
	float PlayTime = 0.0f;
	int   _gKeyEf, _gTrgEf, _KeyEf, _TrgEf;
	int _isEffect = 0;
	float _throw;
	float _hight;
	int _isthrow = 0;

	// �G�t�F�N�g�ʒu
	float _position_x;
	float _position_y;
	float _position_z;


};
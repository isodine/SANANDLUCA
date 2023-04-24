#pragma once
#include"Player.h"
#include "Boss.h"

class SanBomb;
class Damage;
class Boss;
class LKA;

//�T���̃N���X
class SAN :public Player
{
public:
	SAN();
	~SAN();
	//����������
	void Initialize() override;
	//�X�V����
	void Update(Damage& damage, std::vector<std::unique_ptr<IronDoor>>* irondoors);
	//�`�揈��
	void Render(Damage& damage);
	//����擾
	void Input() override;
	//�폜����
	void Terminate() override;
	//�m�b�N�o�b�N
	void KnockBack() override;
	void SetLka(LKA* _lka);
	bool sanBackFlag;


private:
	int  sangauge;
	int  sanicon;
	int  sanframememori;
	int  sanfrask;
	int HPgauge = 0;

	int hpgaugehandle[6];
	int hphandle;
	float oldcount;
	bool _isflag;

	LKA* lka;
};
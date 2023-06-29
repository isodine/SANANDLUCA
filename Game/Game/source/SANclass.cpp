/**
 * @file SANclass.cpp
 * @brief �T�����L�̓�������������v���O����
 * @author �铇����
 * @date December 2022
 *
 * @note HP�Q�[�W�����	@author �c���@�l
 */

#include "AppFrame.h"

SAN::SAN()
	:Player()
{
	SetType(true);
}

SAN::~SAN()
{
}

void SAN::Initialize()
{
	Player::Initialize();
	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��)
	Mhandle = MV1LoadModel("res/01_Character_Model/San_2023_0222/San_Fullmotion.mv1");
	hpgaugehandle[0] = LoadGraph("res/san/HP_san_6.png");
	hpgaugehandle[1] = LoadGraph("res/san/HP_san_5.png");
	hpgaugehandle[2] = LoadGraph("res/san/HP_san_4.png");
	hpgaugehandle[3] = LoadGraph("res/san/HP_san_3.png");
	hpgaugehandle[4] = LoadGraph("res/san/HP_san_2.png");
	hpgaugehandle[5] = LoadGraph("res/san/HP_san_1.png");
	hphandle = LoadGraph("res/san_minus/UI_san_minus.png");
	Mattach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�
	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	// �Đ����Ԃ̏�����
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	// �ʒu,�����̏�����
	vPos = VGet(-60, 0, 0);
	vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���
	oldcount = GetNowCount();
	// ���ʒu�̐ݒ�
	_colSubY = 45.f;
	HP = 6;
	sanBackFlag = false;
}

void SAN::Input()
{
	int keyold1P = Key1P;
	Key1P = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg1P = (Key1P ^ keyold1P) & Key1P;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	key = Key1P;
	trg = Trg1P;
}

void SAN::Terminate() {
	Player::Terminate();
}

void SAN::SetLka(LKA* _lka) {
	lka = _lka;
}

void SAN::KnockBack() {
	BackCount += 1;
	if (sanBackFlag) {
		if (v.x == 0 && v.z == 0) {
			knockBackDir = VScale(VNorm(lka->vDir), 1.5);
		}
		else {
			knockBackDir = VScale(VNorm(vDir), -1.5);
		}
		sanBackFlag = false;
	}
	if (BackCount <= 30 && (hitPolywallback.HitFlag == 0 && hitPolywallside.HitFlag == 0)) {
		vPos = VAdd(vPos, knockBackDir);
	}
	else if(BackCount > 30 && BackCount <= 59){
	}
	else if (BackCount == 60) {
		BackCount = 0;
	}
}

void SAN::Update(Damage& damage, std::vector<std::unique_ptr<IronDoor>>* irondoors)
{
	
	Player::Update(irondoors);
	if (damage.SanHitFlag == true||damage.SanFloorHitFlag == true||damage.SanSlimeHitFlag == true) 
	{
		oldcount = GetNowCount();
	}
	if (damage.SanHitFlag && damage.LkaHitFlag) {
		KnockBack();
	}
}

void SAN::Render(Damage& damage)
{
	Player::Render();
	VECTOR v = ConvWorldPosToScreenPos(vPos);
	if (0.f <= v.z && v.z < 1.f)
	{
		if (Player::HP == 6)
		{
			DrawGraph(0, 0, hpgaugehandle[0], true);
		}
		if (Player::HP == 5)
		{
			DrawGraph(0, 0, hpgaugehandle[1], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 100, v.y - 300, hphandle, true);
			}
		}
		if (Player::HP == 4)
		{
			DrawGraph(0, 0, hpgaugehandle[2], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 100, v.y - 300, hphandle, true);
			}
		}
		if (Player::HP == 3)
		{
			DrawGraph(0, 0, hpgaugehandle[3], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 100, v.y - 300, hphandle, true);
			}
		}
		if (Player::HP == 2)
		{
			DrawGraph(0, 0, hpgaugehandle[4], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 100, v.y - 300, hphandle, true);
			}
		}
		if (Player::HP == 1)
		{
			DrawGraph(0, 0, hpgaugehandle[5], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 100, v.y - 300, hphandle, true);
			}
		}
	}
	
}
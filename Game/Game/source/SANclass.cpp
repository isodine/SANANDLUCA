//#include "SANclass.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"

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
	hphandle[0] = LoadGraph("res/san_v2/UI_san_v6.png");
	hphandle[1] = LoadGraph("res/san_v2/UI_san_v5.png");
	hphandle[2] = LoadGraph("res/san_v2/UI_san_v4.png");
	hphandle[3] = LoadGraph("res/san_v2/UI_san_v3.png");
	hphandle[4] = LoadGraph("res/san_v2/UI_san_v2.png");
	hphandle[5] = LoadGraph("res/san_v2/UI_san_v1.png");
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
}

void SAN::Input()
{
	int keyold1P = Key1P;
	Key1P = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg1P = (Key1P ^ keyold1P) & Key1P;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	key = Key1P;
	trg = Trg1P;
}

void SAN::Update(Damage& damage)
{
	
	Player::Update();
	if (damage.SanHitFlag == true) { oldcount = GetNowCount();}
}

void SAN::Render(Damage& damage)
{
	Player::Render();
	VECTOR v = ConvWorldPosToScreenPos(vPos);
	if (0.f <= v.z && v.z < 1.f)
	{
		if (Player::HP == 6)
		{
			DrawGraph(0, 880, hpgaugehandle[0], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[0], true);
			}
		}
		if (Player::HP == 5)
		{
			DrawGraph(0, 880, hpgaugehandle[1], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[1], true);
			}
		}
		if (Player::HP == 4)
		{
			DrawGraph(0, 880, hpgaugehandle[2], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[2], true);
			}
		}
		if (Player::HP == 3)
		{
			DrawGraph(0, 880, hpgaugehandle[3], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[3], true);
			}
		}
		if (Player::HP == 2)
		{
			DrawGraph(0, 880, hpgaugehandle[4], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[4], true);
			}
		}
		if (Player::HP == 1)
		{
			DrawGraph(0, 880, hpgaugehandle[5], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[5], true);
			}
		}
	}
	
}
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
	sanfrask = LoadGraph("res/pH_gauge/pHgauge_SL_flask.png");
	sangauge = LoadGraph("res/pH_gauge/�Q�[�W�i���j/�_/pHgauge_strongacid.png");
	sanicon = LoadGraph("res/pH_gauge/�A�C�R���\���/�T��/pHgauge_Sun_Emotions_Normal.png");
	sanframememori = LoadGraph("res/pH_gauge/�t���[��/�T��/pHgauge_Sun_background_memori.png");
	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��)
	Mhandle = MV1LoadModel("res/Sun/���f���i�e�N�X�`�����݁j/sun multimotion2.mv1");
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

void SAN::Update()
{
	
	Player::Update();
	
}

void SAN::Render()//(SanBomb& sanB,Damage& damage)
{
	Player::Render();
	DrawGraph(0, 470, sanfrask, TRUE);
	DrawGraph(0, 470, sanicon, TRUE);
	HPgauge = 610 - int((610 / _damage->MaxSanHP) * _damage->SanHP);
	DrawRectGraph(0, 470, 0, 0, 220, 610 - HPgauge, sangauge, true, false);
	/*DrawGraph(0,470,sangauge,TRUE);*/
	DrawGraph(0, 470, sanframememori, TRUE);
	
}
//void SAN::Jump()
//{
//	if (throughtime == 0.f) { height = 10.f; }
//	vPos.y += height;
//
//}
//
//void SAN::freeFall()
//{
//	vPos.y -= throughtime;
//	throughtime += 0.5f;
//}
#include"LKAclass.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"

LKA::LKA()
	:Player()
{
	SetType(false);
}

LKA::~LKA()
{
}

void LKA::Initialize()
{
	Player::Initialize();

	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j
	Mhandle = MV1LoadModel("res/Lka_2023_0222/Lka_Fullmotion.mv1");

	// �ʒu,�����̏�����
	vPos = VGet(60, 20, 0);
	//vPos = VGet(-60, 300, 0);
	// ���ʒu�̐ݒ�
	_colSubY = 45.f;
}

void LKA::Input()
{
	int keyold2P = Key2P;
	Key2P = GetJoypadInputState(DX_INPUT_PAD2);
	Trg2P = (Key2P ^ keyold2P) & Key2P;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	key = Key2P;
	trg = Trg2P;
}

void LKA::Update()
{
	Player::Update();
}

void LKA::Render()
{
	Player::Render();
}
//	void LKA::Jump()
//	{
//		if (throughtime == 0.f) { height = 10.f; }
//		vPos.y += height;
//	}
//
//void LKA::freeFall()
//{
//	vPos.y -= throughtime;
//	throughtime += 0.5f;
//}
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
	Mhandle = MV1LoadModel("res/01_Character_Model/Lka_2023_0222/Lka_Fullmotion.mv1");
	hpgaugehandle[0] = LoadGraph("res/Lka/HP_lka_6.png");
	hpgaugehandle[1] = LoadGraph("res/Lka/HP_lka_5.png");
	hpgaugehandle[2] = LoadGraph("res/Lka/HP_lka_4.png");
	hpgaugehandle[3] = LoadGraph("res/Lka/HP_lka_3.png");
	hpgaugehandle[4] = LoadGraph("res/Lka/HP_lka_2.png");
	hpgaugehandle[5] = LoadGraph("res/Lka/HP_lka_1.png");
	hphandle[0] = LoadGraph("res/lka_v2/UI_lka_v6.png");
	hphandle[1] = LoadGraph("res/lka_v2/UI_lka_v5.png");
	hphandle[2] = LoadGraph("res/lka_v2/UI_lka_v4.png");
	hphandle[3] = LoadGraph("res/lka_v2/UI_lka_v3.png");
	hphandle[4] = LoadGraph("res/lka_v2/UI_lka_v2.png");
	hphandle[5] = LoadGraph("res/lka_v2/UI_lka_v1.png");
	Mattach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�
	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	// �Đ����Ԃ̏�����
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	// �ʒu,�����̏�����
	vPos = VGet(60, 0, 0);
	vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���

	// ���ʒu�̐ݒ�
	_colSubY = 60.f;
	oldcount = GetNowCount();

	_colSubY = 45.f;
	HP = 6;
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
		// �J�������ړ�����
		v.x = v.x / 2; v.y = v.y / 2; v.z = v.z / 2;
		cam._vPos = VAdd(cam._vPos, v);
		cam._vTarget = VAdd(cam._vTarget, v);
	}
	else {
		// ������Ȃ������B���̍��W�ɖ߂�
		vPos = oldvPos;
	}

	// �ړ��ʂ����̂܂܃L�����̌����ɂ���
	if (VSize(v) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
		vDir = v;
		if (!(_status == STATUS::JUMP)) {
			_status = STATUS::WALK;
		}
	}
	else if (throughtime > 0.0f) {}
	else {
		_status = STATUS::WAIT;
	}


	// �f�o�b�O�@�\
	//if (trg & PAD_INPUT_2) {
	//	_bViewCollision = !_bViewCollision;
	//}
	//if (_bViewCollision) {
	//	MV1SetFrameVisible(_handleMap, _frameMapCollision, TRUE);
	//}
	//else {
	//	MV1SetFrameVisible(_handleMap, _frameMapCollision, FALSE);
	//}

	// �X�e�[�^�X���ς���Ă��Ȃ����H
	if (oldStatus == _status) {
		// �Đ����Ԃ�i�߂�
		Mplay_time += 0.5f;
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if (Mattach_index != -1) {
			MV1DetachAnim(Mhandle, Mattach_index);
			Mattach_index = -1;
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		switch (_status) {
		case STATUS::WAIT:
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "idle2"), -1, FALSE);
			break;
		case STATUS::WALK:
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "walk2"), -1, FALSE);
			break;
		case STATUS::JUMP:
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "jump2"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		Mtotal_time = MV1GetAttachAnimTotalTime(Mhandle, Mattach_index);
		// �Đ����Ԃ�������
		Mplay_time = 0.0f;
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (Mplay_time >= Mtotal_time) {
		Mplay_time = 0.0f;
	}
	if (damage.SanHitFlag == true) { oldcount = GetNowCount(); }
}

void LKA::Render(Damage& damage) {
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(Mhandle, Mattach_index, Mplay_time);

	// ���f����`�悷��
	{
		// �ʒu
		MV1SetPosition(Mhandle, vPos);
		// ��������Y����]���Z�o
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(vDir.x * -1, vDir.z * -1);		// ���f�����W���łǂ���������Ă��邩�Ŏ����ς��(�����-z�������Ă���ꍇ)
		MV1SetRotationXYZ(Mhandle, vRot);
		// �`��
		MV1DrawModel(Mhandle);

		//�_���[�W����̕`��
		DrawCapsule3D(VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
		DrawSphere3D(VGet(vPos.x, vPos.y + 50, vPos.z), 55, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);

		// �R���W��������p���C���̕`��
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));
		VECTOR v = ConvWorldPosToScreenPos(vPos);
		if (0.f <= v.z && v.z < 1.f)
		{
			if (damage.LkaHP == 6)
			{
				DrawGraph(0, 880, hpgaugehandle[0], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[0], true);
				}
			}
			if (damage.LkaHP == 5)
			{
				DrawGraph(0, 880, hpgaugehandle[1], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[1], true);
				}
			}
			if (damage.LkaHP == 4)
			{
				DrawGraph(0, 880, hpgaugehandle[2], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[2], true);
				}
			}
			if (damage.LkaHP == 3)
			{
				DrawGraph(0, 880, hpgaugehandle[3], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[3], true);
				}
			}
			if (damage.LkaHP == 2)
			{
				DrawGraph(0, 880, hpgaugehandle[4], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[4], true);
				}
			}
			if (damage.LkaHP == 1)
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
}
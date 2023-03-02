#include"SANclass.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

SAN::SAN()
	:Player()
{
}

SAN::~SAN()
{
}

void SAN::Initialize()
{
	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��)
	Mhandle = MV1LoadModel("res/Sun/���f���i�e�N�X�`�����݁j/sun multimotion2.mv1");
	hphandle[0] = LoadGraph("res/UI_san_v6.png");
	hphandle[1] = LoadGraph("res/UI_san_v5.png");
	Mattach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�
	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	// �Đ����Ԃ̏�����
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	// �ʒu,�����̏�����
	vPos = VGet(-60, 0, 0);
	vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���

	// ���ʒu�̐ݒ�
	_colSubY = 60.f;
}

void SAN::Input()
{
	int keyold1P = Key1P;
	Key1P = GetJoypadInputState(DX_INPUT_PAD1);
	Trg1P = (Key1P ^ keyold1P) & Key1P;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
}

void SAN::Update(Camera& cam) 
{
	Input();
	//int key = ApplicationMain::GetInstance()->GetKey1P();
	//int trg = ApplicationMain::GetInstance()->GetTrg1P();
	int key = Key1P;
	int trg = Trg1P;
	//std::unique_ptr<Camera> cam = std::make_unique<Camera>();

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATUS oldStatus = _status;
	// �J�����̌����Ă���p�x���擾
	float sx = cam._vPos.x - cam._vTarget.x;
	float sz = cam._vPos.z - cam._vTarget.z;
	float camrad = atan2(sz, sx);

	// �ړ����������߂�
	VECTOR v = { 0,0,0 };
	float mvSpeed = 6.f;
	//if (key & PAD_INPUT_RIGHT) { v.x = 1; }
	//if (key & PAD_INPUT_LEFT) { v.x = -1; }
	//if (key & PAD_INPUT_DOWN) { v.z = -1; }
	//if (key & PAD_INPUT_UP) { v.z = 1; }

	if (key & PAD_INPUT_DOWN) { v.x = 1; }
	if (key & PAD_INPUT_UP) { v.x = -1; }
	if (key & PAD_INPUT_LEFT) { v.z = -1; }
	if (key & PAD_INPUT_RIGHT) { v.z = 1; }
	if (key & PAD_INPUT_10 && !(_status == STATUS::JUMP)) { _status = STATUS::JUMP; }

	if (_status == STATUS::JUMP) { charJump(); }
	// v��rad����]������
	float length = 0.f;
	if (VSize(v) > 0.f) { length = mvSpeed; }
	float rad = atan2(v.z, v.x);
	v.x = cos(rad + camrad) * length;
	v.z = sin(rad + camrad) * length;

	// �ړ��O�̈ʒu��ۑ�
	VECTOR oldvPos = vPos;

	// v�̕��ړ�
	vPos = VAdd(vPos, v);

	// �ړ�������ŃR���W��������
	MV1_COLL_RESULT_POLY hitPoly;
	// ��l���̍��ʒu���牺�����ւ̒���
	hitPoly = MV1CollCheck_Line(_handleMap, _frameMapCollision,
		VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		// ��������
		if (vPos.y < hitPoly.HitPosition.y) {
			throughtime = 0.0f;
			height = 0.0f;
			vPos.y = 0.f;
			_status = STATUS::WAIT;
		}
		// ��������Y�ʒu���L�������W�ɂ���
		vPos.y = hitPoly.HitPosition.y + height;

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
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "move2"), -1, FALSE);
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
}

void SAN::Render()
{
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
		MV1SetScale(Mhandle, VGet(1.0f, 1.0f, 1.0f));
		MV1DrawModel(Mhandle);

		//�_���[�W����̕`��
		DrawCapsule3D(VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
		DrawSphere3D(VGet(vPos.x, vPos.y + 50, vPos.z), 55, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);

		// �R���W��������p���C���̕`��
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));

		VECTOR v = ConvWorldPosToScreenPos(vPos);
		if (0.f <= v.z && v.z < 1.f)
		{
			DrawGraph(v.x, v.y, hphandle[0], true);
		}

	}
	//DrawFormatString(0, 260, GetColor(255, 255, 255), "%f, %f, %f", vPos.x, vPos.y, vPos.z);
}
#include"LKAclass.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include <string>
#include <memory>
#include <vector>

LKA::LKA()
{
}

LKA::~LKA()
{
}

void LKA::Initialize()
{

}

void LKA::Update() {
	int key = ApplicationMain::GetInstance()->GetKey1P();
	int trg = ApplicationMain::GetInstance()->GetTrg1P();

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATUS oldStatus = _status;
	// �J�����̌����Ă���p�x���擾
	float sx = _cam._vPos.x - _cam._vTarget.x;
	float sz = _cam._vPos.z - _cam._vTarget.z;
	float camrad = atan2(sz, sx);

	// �ړ����������߂�
	VECTOR v = { 0,0,0 };
	float mvSpeed = 6.f;
	if (key & PAD_INPUT_5) { v.x = 1; }
	if (key & PAD_INPUT_8) { v.x = -1; }
	if (key & PAD_INPUT_4) { v.z = -1; }
	if (key & PAD_INPUT_6) { v.z = 1; }

	//if (key & PAD_INPUT_DOWN) { v.x = 1; }
	//if (key & PAD_INPUT_UP) { v.x = -1; }
	//if (key & PAD_INPUT_LEFT) { v.z = -1; }
	//if (key & PAD_INPUT_RIGHT) { v.z = 1; }
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
	hitPoly = MV1CollCheck_Line(_handleMap, ModeGame::_frameMapCollision,
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
		_cam._vPos = VAdd(_cam._vPos, v);
		_cam._vTarget = VAdd(_cam._vTarget, v);
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
		_play_time += 0.5f;
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if (_attach_index != -1) {
			MV1DetachAnim(_handle, _attach_index);
			_attach_index = -1;
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		switch (_status) {
		case STATUS::WAIT:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "Anim003"), -1, FALSE);
			break;
		case STATUS::WALK:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "Anim004"), -1, FALSE);
			break;
		case STATUS::JUMP:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "Anim002"), -1, FALSE);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		Mtotal_time = MV1GetAttachAnimTotalTime(_handle, _attach_index);
		// �Đ����Ԃ�������
		Mplay_time = 0.0f;
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (_play_time >= _total_time) {
		_play_time = 0.0f;
	}
}

void LKA::Render() {}
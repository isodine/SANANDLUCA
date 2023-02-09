#include"LKAclass.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"

LKA::LKA()
	:Player()
{
}

LKA::~LKA()
{
}

void LKA::Initialize()
{
	Player::Initialize(mypH);

	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j
	Mhandle = MV1LoadModel("res/Lka/Lka multimotion.mv1");

	// �ʒu,�����̏�����
	vPos = VGet(60, 20, 0);

	// ���ʒu�̐ݒ�
	_colSubY = 45.f;
}

void LKA::Input()
{
	int keyold2P = Key2P;
	Key2P = GetJoypadInputState(DX_INPUT_PAD2);
	Trg2P = (Key2P ^ keyold2P) & Key2P;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
}

void LKA::Update(Camera& cam)
{
	Input();
	int key = Key2P;
	int trg = Trg2P;

	Player::Update(mypH);

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATUS oldStatus = _status;
	// �J�����̌����Ă���p�x���擾
	float sx = cam._vPos.x - cam._vTarget.x;
	float sz = cam._vPos.z - cam._vTarget.z;
	float camrad = atan2(sz, sx);

	// �ړ����������߂�
	VECTOR v = { 0,0,0 };
	float mvSpeed = 6.f;

	if (key & PAD_INPUT_DOWN) { v.x = 1; }
	if (key & PAD_INPUT_UP) { v.x = -1; }
	if (key & PAD_INPUT_LEFT) { v.z = -1; }
	if (key & PAD_INPUT_RIGHT) { v.z = 1; }
	if (key & PAD_INPUT_1 && !(_status == STATUS::JUMP)) { _status = STATUS::JUMP; }

	if (_status == STATUS::JUMP) { Jump(cam); }
	// v��rad����]������
	float length = 0.f;
	if (VSize(v) > 0.f) { length = mvSpeed; }
	float rad = atan2(v.z, v.x);
	v.x = cos(rad + camrad) * length;
	v.z = sin(rad + camrad) * length;

	// �ړ��O�̈ʒu��ۑ�
	oldPos = vPos;



	// ��ʓ��ɃL�����N�^�[�������Ă��Ȃ����ǂ�����`�悷��
//TRUE�͓����ĂȂ��AFALSE�͓����Ă�
	if (CheckCameraViewClip(vPos) == TRUE)
	{
		// ��ʊO�ɏo���B���̍��W�ɖ߂�
		vPos = oldPos;
		v = { 0,0,0 };
	}

	// v�̕��ړ�
	this->vPos = VAdd(this->vPos, v);

	// �J�������ړ�����
	v.x = v.x / 2.0f; v.y = v.y / 2.0f; v.z = v.z / 2;
	cam._vPos = VAdd(cam._vPos, v);
	cam._vTarget = VAdd(cam._vTarget, v);

	// �ړ�������ŃR���W��������
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	MV1_COLL_RESULT_POLY hitPolyfloor;
	MV1_COLL_RESULT_POLY hitPolywall;

	hitPolywall = MV1CollCheck_Line(_handleMap, frameMapCollisionwall,
		VAdd(vPos, VGet(0, _colSubY, -50)), VAdd(vPos, VGet(0, _colSubY, 500.f)));
	if (hitPolywall.HitFlag && (vPos.z + 30 >= hitPolywall.HitPosition.z))
	{
		float backwidth = hitPolywall.HitPosition.z - vPos.z + 30;
		float subX = vPos.x - oldPos.x;
		float subZ = vPos.z - oldPos.z;
		vPos.x = oldPos.x/*- subX*/;
		vPos.z = oldPos.z/*- subZ*/;

		cam._vPos.x -= subX / 2;
		cam._vPos.z -= subZ / 2;
		cam._vTarget.x -= subX / 2;
		cam._vTarget.z -= subZ / 2;
		v = { 0,0,0 };
	}

	// ��l���̍��ʒu���牺�����ւ̒���
	hitPolyfloor = MV1CollCheck_Line(_handleMap, frameMapCollisionfloor,
		VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)));

	hitPolyDim = MV1CollCheck_Capsule(_handleMap, frameMapCollisionfloor,
		VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f);
	if (hitPolyDim.HitNum >= 1)
	{
		// ��������
		if (vPos.y < hitPolyfloor.HitPosition.y)
		{
			_status = STATUS::WAIT;
			throughtime = 0.0f;
			float minusY = vPos.y;
			// ��������Y�ʒu���L�������W�ɂ���
			vPos.y = hitPolyfloor.HitPosition.y - 0.5f;
			cam._vPos.y += (vPos.y - minusY) / 2;
			cam._vTarget.y += (vPos.y - minusY) / 2;
		}
	}
	else {
		// ������Ȃ������B���̍��W�ɖ߂�
		freeFall(cam);
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
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "jamp2"), -1, FALSE);
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

void LKA::Render()
{
	Player::Render(mypH);

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
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, -50)), VAdd(vPos, VGet(0, _colSubY, 500.f)), GetColor(255, 0, 0));

	}
	int x = 0, y = 106, size = 16;
	SetFontSize(size);
	switch (_status)
	{
	case Player::STATUS::WAIT:
		DrawFormatString(x, y, GetColor(255, 0, 0), "Lka states = WAIT");
		break;
	case Player::STATUS::WALK:
		DrawFormatString(x, y, GetColor(255, 0, 0), "Lka states = WALK");
		break;
	case Player::STATUS::JUMP:
		DrawFormatString(x, y, GetColor(255, 0, 0), "Lka states = JUMP");
		break;
	}
}
void LKA::Jump(Camera& cam)
{
	if (throughtime == 0.f) { height = 10.f; }
	vPos.y += height;
	cam._vPos.y += height / 2;
	cam._vTarget.y += height / 2;
}

void LKA::freeFall(Camera& cam)
{
	vPos.y -= throughtime;
	cam._vPos.y -= throughtime / 2;
	cam._vTarget.y -= throughtime / 2;
	throughtime += 0.5f;
}
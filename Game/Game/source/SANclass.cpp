//#include "SANclass.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"

SAN::SAN()
	:Player()
{
}

SAN::~SAN()
{
}

void SAN::Initialize()
{
	Player::Initialize(mypH);

	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��)
	Mhandle = MV1LoadModel("res/San_2023_0130/San_Fullmotion_2023_0203.mv1");

	// �ʒu,�����̏�����
	vPos = VGet(-60, 20, 0);

	// ���ʒu�̐ݒ�
	_colSubY = 45.f;

}

void SAN::Input()
{
	int keyold1P = Key1P;
	Key1P = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg1P = (Key1P ^ keyold1P) & Key1P;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
}

void SAN::Update(Camera& cam, SanBomb& sanB)
{
	Input();
	int key = Key1P;
	int trg = Trg1P;

	Player::Update(mypH);

	if (key & PAD_INPUT_5) {	//����L1�{�^��
		// �p�x�ύX
		// Y����]
		float sx = cam._vPos.x - cam._vTarget.x;
		float sz = cam._vPos.z - cam._vTarget.z;
		float rad = atan2(sz, sx);
		float length = sqrt(sz * sz + sx * sx);
		if (key & PAD_INPUT_LEFT) { rad -= 0.05f; }
		if (key & PAD_INPUT_RIGHT) { rad += 0.05f; }
		cam._vPos.x = cam._vTarget.x + cos(rad) * length;
		cam._vPos.z = cam._vTarget.z + sin(rad) * length;

		// Y�ʒu
		if (key & PAD_INPUT_DOWN) { cam._vPos.y -= 5.f; }
		if (key & PAD_INPUT_UP) { cam._vPos.y += 5.f; }
	}
	else {

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
		//if (key & PAD_INPUT_2 && !(_status == STATUS::CHARGE)) { _status = STATUS::CHARGE; }
		//if (key & PAD_INPUT_3 && !(_status == STATUS::ATTACK)) { _status = STATUS::ATTACK; }
		//if (key & PAD_INPUT_4 && !(_status == STATUS::DAMAGE)) { _status = STATUS::DAMAGE; }
		if (key & PAD_INPUT_10) { _status = STATUS::DOWN; }

		if (sanB.situation == None) { attack = Attack::None; }
		if (key & PAD_INPUT_6 && (attack == Attack::None)) { 
			attack = Attack::Pop;
		}
		if (sanB.situation == Keep) { attack = Attack::Keep; }
		if (key & PAD_INPUT_6 && (attack == Attack::Keep)) { attack = Attack::Throw; }
		if (_status == STATUS::JUMP) { Jump(cam); }
		// v��rad����]������
		float length = 0.f;
		if (VSize(v) > 0.f) { length = mvSpeed; }
		float rad = atan2(v.z, v.x);
		v.x = cos(rad + camrad) * length;
		v.z = sin(rad + camrad) * length;

		// �ړ��O�̈ʒu��ۑ�
		VECTOR oldvPos = vPos;



		// ��ʓ��ɃL�����N�^�[�������Ă��Ȃ����ǂ�����`�悷��
		//TRUE�͓����ĂȂ��AFALSE�͓����Ă�
		if (CheckCameraViewClip(vPos) == TRUE)
		{
			// ��ʊO�ɏo���B���̍��W�ɖ߂�
			vPos = oldvPos;
			v = { 0,0,0 };
		}


		// v�̕��ړ�
		vPos = VAdd(vPos, v);

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
			float subX = vPos.x - oldvPos.x;
			float subZ = vPos.z - oldvPos.z;
			vPos.x = oldvPos.x/*- subX*/;
			vPos.z = oldvPos.z/*- subZ*/;

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
		else
		{
			_status = STATUS::WAIT;
		}



		sanB.Update(this);         //�{���̍X�V



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
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "idle"), -1, FALSE);
				break;
			case STATUS::WALK:
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "move"), -1, FALSE);
				break;
			case STATUS::JUMP:
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "jamp1"), -1, FALSE);
				break;
			case STATUS::DAMAGE:
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "damage"), -1, FALSE);
				break;
			case STATUS::CHARGE:
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "attack1"), -1, FALSE);
				break;
			case STATUS::ATTACK:
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "attack2"), -1, FALSE);
				break;
			case STATUS::DOWN:
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "down"), -1, FALSE);
				break;
			}

			// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
			Mtotal_time = MV1GetAttachAnimTotalTime(Mhandle, Mattach_index);
			// �Đ����Ԃ�������
			Mplay_time = 0.0f;
			//if(!(oldStatus== STATUS::JUMP)&& _status== STATUS::JUMP)
			//{
			//	Mplay_time = 20.0f;
			//}
		}

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (Mplay_time >= Mtotal_time)
		{
			Mplay_time = 0.0f;
		}
	}
}

void SAN::Render(SanBomb& sanB)
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
		//MV1SetScale(Mhandle, VGet(10.0f, 10.0f, 10.0f));
		//MV1SetFrameOpacityRate(Mhandle, 0, 0.0f);
		//MV1SetOpacityRate(Mhandle, 0.3f);
		//MV1SetMaterialDrawBlendMode(Mhandle, 0, DX_BLENDMODE_ALPHA);
		//MV1SetMaterialDrawBlendParam(Mhandle, 0, 100);
		MV1DrawModel(Mhandle);

		//�_���[�W����̕`��
		DrawCapsule3D(VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
		DrawSphere3D(VGet(vPos.x, vPos.y + 50, vPos.z), 55, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);

		// �R���W��������p���C���̕`��
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, -50)), VAdd(vPos, VGet(0, _colSubY, 500.f)), GetColor(255, 0, 0));

	}
	sanB.Render();
	//DrawFormatString(0, 260, GetColor(255, 255, 255), "%f, %f, %f", vPos.x, vPos.y, vPos.z);
}
void SAN::Jump(Camera& cam)
{
	if (throughtime == 0.f) { height = 10.f; }
	vPos.y += height;
	cam._vPos.y += height / 2;
	cam._vTarget.y += height / 2;

}

void SAN::freeFall(Camera& cam)
{
	vPos.y -= throughtime;
	cam._vPos.y -= throughtime / 2;
	cam._vTarget.y -= throughtime / 2;
	throughtime += 0.5f;
}
#include "Player.h"
//#include "ModeGame.h"
#include "ModeBoss.h"

//extern int _handleMap;
//extern int _handleSkySphere;
//extern int frameMapCollisionfloor;
//extern int frameMapCollisionwall;

Player::Player()
{
}

Player::~Player()
{
}

void Player::SetBomb(PlayerBomb* bomb)
{
	_bomb = bomb;
}
void Player::SetCamera(Camera* camera)
{
	_camera = camera;

}

void Player::SetDamage(Damage* damage)
{
	_damage = damage;
}

void Player::SetType(bool isSan)
{
	if (isSan)
	{
		mypH = San;
	}
	else
	{
		mypH = Lka;
	}
}

void Player::Input() {

}

void Player::Initialize()
{
	Mattach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�
	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	// �Đ����Ԃ̏�����
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���
	attack = Attack::None;
	SEjump = LoadSoundMem("res/06_Sound/03_SE/ani_ta_biyon02.mp3");
	/*sanfrask = LoadGraph("res/pH_gauge/pHgauge_SL_flask.png");
	sangauge = LoadGraph("res/pH_gauge/�Q�[�W�i���j/�_/pHgauge_strongacid.png");
	sanicon = LoadGraph("res/pH_gauge/�A�C�R���\���/�T��/pHgauge_Sun_Emotions_Normal.png");
	sanframememori = LoadGraph("res/pH_gauge/�t���[��/�T��/pHgauge_Sun_background_memori.png");*/

	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��)
	Mhandle = MV1LoadModel("res/San_2023_0130/San_Fullmotion_2023_0203.mv1");

	// �ʒu,�����̏�����
	vPos = VGet(-60, 20, 0);

	// ���ʒu�̐ݒ�
	_colSubY = 45.f;


}

void Player::Update()
{
	Input();
	/*int key = Key1P;
	int trg = Trg1P;*/

	if (key & PAD_INPUT_5) {	//����L1�{�^��
		// �p�x�ύX
		// Y����]
		
			//float sx = _camera->_vPos.x - _camera->_vTarget.x;
			//float sz = _camera->_vPos.z - _camera->_vTarget.z;
			//float rad = atan2(sz, sx);
			//float length = sqrt(sz * sz + sx * sx);
			//if (key & PAD_INPUT_LEFT) { rad -= 0.05f; }
			//if (key & PAD_INPUT_RIGHT) { rad += 0.05f; }
			//_camera->_vPos.x = _camera->_vTarget.x + cos(rad) * length;
			//_camera->_vPos.z = _camera->_vTarget.z + sin(rad) * length;

			//// Y�ʒu
			//if (key & PAD_INPUT_DOWN) { _camera->_vPos.y -= 5.f; }
			//if (key & PAD_INPUT_UP) { _camera->_vPos.y += 5.f; }
		
	}
	else {

		// �����O�̃X�e�[�^�X��ۑ����Ă���
		STATUS oldStatus = _status;
		// �J�����̌����Ă���p�x���擾
		float sx = _camera->_vPos.x - _camera->_vTarget.x;
		float sz = _camera->_vPos.z - _camera->_vTarget.z;
		float camrad = atan2(sz, sx);

		// �ړ����������߂�
		VECTOR v = { 0,0,0 };
		float mvSpeed = 6.f;
		if (key & PAD_INPUT_DOWN) { v.x = 1; }
		if (key & PAD_INPUT_UP) { v.x = -1; }
		if (key & PAD_INPUT_LEFT) { v.z = -1; }
		if (key & PAD_INPUT_RIGHT) { v.z = 1; }
		if (key & PAD_INPUT_1 && !(_status == STATUS::JUMP)) 
		{ _status = STATUS::JUMP; PlaySoundMem(SEjump, DX_PLAYTYPE_BACK, true); }
		//if (key & PAD_INPUT_2 && !(_status == STATUS::CHARGE)) { _status = STATUS::CHARGE; }
		//if (key & PAD_INPUT_3 && !(_status == STATUS::ATTACK)) { _status = STATUS::ATTACK; }
		//if (key & PAD_INPUT_4 && !(_status == STATUS::DAMAGE)) { _status = STATUS::DAMAGE; }
		if (key & PAD_INPUT_10) { _status = STATUS::DOWN; }

		if (_bomb->situation == None) { attack = Attack::None; }
		if (trg & PAD_INPUT_6 && (attack == Attack::None)) {
			attack = Attack::Pop;
		}
		if (_bomb->situation == Keep) { attack = Attack::Keep; }
		if (trg & PAD_INPUT_6 && (attack == Attack::Keep)) { attack = Attack::Throw; }
		if (_status == STATUS::JUMP) { Jump(); }
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


		// �ړ�������ŃR���W��������
		MV1_COLL_RESULT_POLY_DIM hitPolyDim;
		MV1_COLL_RESULT_POLY hitPolyfloor;
		MV1_COLL_RESULT_POLY hitPolywallback;
		MV1_COLL_RESULT_POLY hitPolywallside;

		
			hitPolywallback = MV1CollCheck_Line(stageHandle, wallCol,
				VAdd(vPos, VGet(0, _colSubY, -50)), VAdd(vPos, VGet(0, _colSubY, 500.f)));
			if (hitPolywallback.HitFlag && (vPos.z + 30 >= hitPolywallback.HitPosition.z)){
				float backwidth = hitPolywallback.HitPosition.z - vPos.z + 30;
				float subX = vPos.x - oldvPos.x;
				float subZ = vPos.z - oldvPos.z;
				vPos.x = oldvPos.x;
				vPos.z = oldvPos.z;

				v = { 0,0,0 };
			}

			hitPolywallside = MV1CollCheck_Line(stageHandle, wallCol,
				VAdd(vPos, VGet(-50, _colSubY, 0)), VAdd(vPos, VGet(500.f, _colSubY, 0)));
			if (hitPolywallside.HitFlag && (vPos.x + 30 >= hitPolywallside.HitPosition.x)) {
				float sidewidth = hitPolywallside.HitPosition.x - vPos.x + 30;
				float subX = vPos.x - oldvPos.x;
				float subZ = vPos.z - oldvPos.z;
				vPos.x = oldvPos.x;
				vPos.z = oldvPos.z;

				v = { 0,0,0 };
			}

			// ��l���̍��ʒu���牺�����ւ̒���
			hitPolyfloor = MV1CollCheck_Line(stageHandle, floorCol,
				VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)));

			hitPolyDim = MV1CollCheck_Capsule(stageHandle, floorCol,
				VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f);
			if (hitPolyDim.HitNum >= 1)
			{
				// ��������
				if (vPos.y < hitPolyfloor.HitPosition.y)
				{
					Landing(hitPolyfloor.HitPosition.y);
				}
			}
			else {
				freeFall();
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



		//sanB.Update(this);         //�{���̍X�V



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
				Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "walk"), -1, FALSE);
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

void Player::Jump() 
{
	if (throughtime == 0.f) { height = 10.f; }
	vPos.y += height;
}

void Player::freeFall()
{
	vPos.y -= throughtime;
	throughtime += 0.5f;
}

void Player::Render()
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
		MV1DrawModel(Mhandle);

		//�_���[�W����̕`��
		DrawCapsule3D(VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
		DrawSphere3D(VGet(vPos.x, vPos.y + 50, vPos.z), 55, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);

		// �R���W��������p���C���̕`��
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, -50)), VAdd(vPos, VGet(0, _colSubY, 500.f)), GetColor(255, 0, 0));

	}
	int x = 0, y = 106, size = 16;
	SetFontSize(size);
	/*switch (_status)
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
	}*/
}


void Player::charJump() {
	height += 10.0f - throughtime;
	throughtime += 0.5f;
}

void Player::Landing(float HitYPos) {
	_status = STATUS::WAIT;
	throughtime = 0.0f;
	//float minusY = vPos.y;
	// ��������Y�ʒu���L�������W�ɂ���
	vPos.y = HitYPos - 0.5f;
}

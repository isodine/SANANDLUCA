#include "Gimmick.h"


Gimmick::Gimmick() {
	BalanceHandle = MV1LoadModel("res/Balance_MOmarge.mv1");
	SanHitFlag = false;
	LkaHitFlag = false;
}

void Gimmick::Initialize()
{
	MV1SetupCollInfo(BalanceHandle, 3, 8, 8, 8);  //�T���̎M
	MV1SetupCollInfo(BalanceHandle, 4, 8, 8, 8);  //���J�̎M

}

void Gimmick::Terminate() {

}

void Gimmick::Process() {

}

void Gimmick::Balance(VECTOR SanPos, VECTOR LkaPos) {

	
	MV1RefreshCollInfo(BalanceHandle, 3, 8);  //�T���̎M
	MV1RefreshCollInfo(BalanceHandle, 4, 8);  //���J�̎M

	BALANCE oldBalance = balance;

	MV1_COLL_RESULT_POLY_DIM hitPolyDim1;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim2;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim3;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim4;

	MV1_COLL_RESULT_POLY hitPoly1;
	// �T���̍��ʒu���牺�����ւ̒����ƃT���̎M
	hitPoly1 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(SanPos, VGet(0, 60.f, 0)), VAdd(SanPos, VGet(0, -99999.f, 0)));

	MV1_COLL_RESULT_POLY hitPoly2;
	// ���J�̍��ʒu���牺�����ւ̒����ƃT���̎M
	hitPoly2 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(LkaPos, VGet(0, 60.f, 0)), VAdd(LkaPos, VGet(0, -99999.f, 0)));

	MV1_COLL_RESULT_POLY hitPoly3;
	// �T���̍��ʒu���牺�����ւ̒����ƃ��J�̎M
	hitPoly3 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(SanPos, VGet(0, 60.f, 0)), VAdd(SanPos, VGet(0, -99999.f, 0)));

	MV1_COLL_RESULT_POLY hitPoly4;
	// ���J�̍��ʒu���牺�����ւ̒����ƃ��J�̎M
	hitPoly4 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(LkaPos, VGet(0, 60.f, 0)), VAdd(LkaPos, VGet(0, -99999.f, 0)));

	

	hitPolyDim1 = MV1CollCheck_Capsule(BalanceHandle, 3,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);  //�T�����T���̎M�ɏ�����Ƃ�
	hitPolyDim2 = MV1CollCheck_Capsule(BalanceHandle, 4,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);  //���J�����J�̎M�ɏ�����Ƃ�
	hitPolyDim3 = MV1CollCheck_Capsule(BalanceHandle, 3,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);  //���J���T���̎M�ɏ�����Ƃ�
	hitPolyDim4 = MV1CollCheck_Capsule(BalanceHandle, 4,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);  //�T�������J�̎M�ɏ�����Ƃ�

	if (hitPolyDim1.HitNum >= 1) {
		SanHitFlag = true;
		player.vPos.y = hitPoly1.HitPosition.y;
	}
	else {
		SanHitFlag = false;
	}

	if(hitPolyDim2.HitNum >= 1) {
		LkaHitFlag = true;
		lka.vPos = hitPoly4.HitPosition;
	}
	else {
		LkaHitFlag = false;
	}

	if (hitPolyDim3.HitNum >= 1) {
		LkaHitFlag = true;
		lka.vPos = hitPoly2.HitPosition;
	}
	else {
		LkaHitFlag = false;
	}

	if (hitPolyDim4.HitNum >= 1) {
		LkaHitFlag = true;
		san.vPos = hitPoly3.HitPosition;
	}
	else {
		LkaHitFlag = false;
	}

	if ((SanHitFlag == false && LkaHitFlag == false) || (SanHitFlag == true && LkaHitFlag == true)) {
		balance = BALANCE::EQUAL;
	}
	else if (SanHitFlag == true && LkaHitFlag == false) {
		balance = BALANCE::SAN;
	}
	else if (SanHitFlag == false && LkaHitFlag == true) {
		balance = BALANCE::LKA;
	}


	if (oldBalance == balance) {
		PlayBalance += 1.0f;
		if (PlayBalance >= TotalBalance)
		{
			PlayBalance = 0.0f;
		}
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if (AttachAnim1 != -1 || AttachAnimSAN != -1 || AttachAnimLKA != -1) {
			MV1DetachAnim(BalanceHandle, AttachAnim1);
			AttachAnim1 = -1;
			MV1DetachAnim(BalanceHandle, AttachAnimSAN);
			AttachAnimSAN = -1;
			MV1DetachAnim(BalanceHandle, AttachAnimLKA);
			AttachAnimLKA = -1;
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�������A�^�b�`����
		switch (balance) {
		case BALANCE::EQUAL:
			AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//�������[�V�������A�^�b�`����
			AttachAnimSAN = MV1AttachAnim(BalanceHandle, 1, -1, FALSE);//���X�����[�V�������A�^�b�`����
			AttachAnimLKA = MV1AttachAnim(BalanceHandle, 2, -1, FALSE);//�E�X�����[�V�������A�^�b�`����
			break;
		case BALANCE::SAN:
			AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//�������[�V�������A�^�b�`����
			AttachAnimSAN = MV1AttachAnim(BalanceHandle, 1, -1, FALSE);//���X�����[�V�������A�^�b�`����
			break;
		case BALANCE::LKA:
			AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//�������[�V�������A�^�b�`����
			AttachAnimLKA = MV1AttachAnim(BalanceHandle, 2, -1, FALSE);//�E�X�����[�V�������A�^�b�`����
			break;
		}
		TotalBalance = MV1GetAttachAnimTotalTime(BalanceHandle, AttachAnim1);
		PlayBalance = 0.0f;
	}

	MV1SetAttachAnimTime(BalanceHandle, AttachAnim1, PlayBalance);
}



void Gimmick::Render() {

	MV1SetPosition(BalanceHandle, VGet(-80.0f, 200.0f, 210.0f));
	MV1DrawModel(BalanceHandle);
}

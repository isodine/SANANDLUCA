#include "Gimmick.h"


Gimmick::Gimmick() {
	BalanceHandle = MV1LoadModel("res/Balance/Motion/Balance_GEONew.mv1");
	SanHitFlag = false;
	LkaHitFlag = false;
	balance = BALANCE::EQUAL;
	AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
	AttachAnimSAN = -1;
	AttachAnimLKA = -1;
	BlendRate = 0;
	BalanceFlag = false;
	EnumFlag = false;
}

void Gimmick::Initialize()
{
	MV1SetPosition(BalanceHandle, VGet(35.0f, 200.0f, 900.0f));
	MV1SetupCollInfo(BalanceHandle, 3, 8, 8, 8);  //サンの皿
	MV1SetupCollInfo(BalanceHandle, 4, 8, 8, 8);  //ルカの皿

}

void Gimmick::Terminate() {

}

void Gimmick::Process() {

}

void Gimmick::Balance(VECTOR SanPos, VECTOR LkaPos) {

	MV1RefreshCollInfo(BalanceHandle, 3, 8);  //サンの皿
	MV1RefreshCollInfo(BalanceHandle, 4, 8);  //ルカの皿

	BALANCE oldBalance = balance;

	if (balance != oldBalance) {
		EnumFlag = true;
	}

	if (EnumFlag) {
		OldBalance = oldBalance;
		EnumFlag = false;
	}

	MV1_COLL_RESULT_POLY hitPoly1;
	MV1_COLL_RESULT_POLY hitPoly2;
	MV1_COLL_RESULT_POLY hitPoly3;
	MV1_COLL_RESULT_POLY hitPoly4;


	hitPoly1 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(san->vPos, VGet(0, san->_colSubY, 0)), VAdd(san->vPos, VGet(0, -1.f, 0)));
	hitPoly2 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(lka->vPos, VGet(0, lka->_colSubY, 0)), VAdd(lka->vPos, VGet(0, -1.f, 0)));
	hitPoly3 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(lka->vPos, VGet(0, lka->_colSubY, 0)), VAdd(lka->vPos, VGet(0, -1.f, 0)));
	hitPoly4 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(san->vPos, VGet(0, san->_colSubY, 0)), VAdd(san->vPos, VGet(0, -1.f, 0)));
	//toDoプレイヤーが浮くバグあり
	if (hitPoly1.HitFlag || hitPoly3.HitFlag) {
		if (hitPoly1.HitFlag) {
			SanHitFlag = true;
			san->Landing(hitPoly1.HitPosition.y);
		}
		else {
			SanHitFlag = false;
			lka->Landing(hitPoly3.HitPosition.y);
		}
	}
	else {
		SanHitFlag = false;
	}

	if (hitPoly2.HitFlag || hitPoly4.HitFlag) {
		if (hitPoly2.HitFlag) {
			LkaHitFlag = true;
			lka->Landing(hitPoly2.HitPosition.y);
		}
		else {
			LkaHitFlag = false;
			san->Landing(hitPoly4.HitPosition.y);
		}
	}
	/*else {
		LkaHitFlag = false;
	}*/

	if ((SanHitFlag == false && LkaHitFlag == false) || (SanHitFlag == true && LkaHitFlag == true) && OldBalance == oldBalance) {
		balance = BALANCE::EQUAL;
		BalanceFlag = true;
	}
	else if (SanHitFlag == true && LkaHitFlag == false && OldBalance == oldBalance) {
		balance = BALANCE::SAN;
		BalanceFlag = true;
	}
	else if (SanHitFlag == false && LkaHitFlag == true && OldBalance == oldBalance) {
		balance = BALANCE::LKA;
		BalanceFlag = true;
	}


	if (oldBalance == balance) {
		PlayBalance += 1.0f;
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (AttachAnim1 != -1 || AttachAnimSAN != -1 || AttachAnimLKA != -1) {
			MV1DetachAnim(BalanceHandle, AttachAnim1);
			AttachAnim1 = -1;
			MV1DetachAnim(BalanceHandle, AttachAnimSAN);
			AttachAnimSAN = -1;
			MV1DetachAnim(BalanceHandle, AttachAnimLKA);
			AttachAnimLKA = -1;
		}

		// ステータスに合わせてアニメーションをアタッチする
		switch (balance) {
		case BALANCE::EQUAL:
			AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
			if (OldBalance == BALANCE::SAN) {
				AttachAnimSAN = MV1AttachAnim(BalanceHandle, 1, -1, FALSE);//左傾きモーションをアタッチする
			}
			else if (OldBalance == BALANCE::LKA) {
				AttachAnimLKA = MV1AttachAnim(BalanceHandle, 2, -1, FALSE);//右傾きモーションをアタッチする
			}
			else {

			}
			break;
		case BALANCE::SAN:
			AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
			AttachAnimSAN = MV1AttachAnim(BalanceHandle, 1, -1, FALSE);//左傾きモーションをアタッチする
			break;
		case BALANCE::LKA:
			AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
			AttachAnimLKA = MV1AttachAnim(BalanceHandle, 2, -1, FALSE);//右傾きモーションをアタッチする
			break;
		}
	}

	if (BalanceFlag && BlendRate >= 1) {
		BlendRate = 0;
		BalanceFlag = false;
	}
	else {
		BalanceFlag = false;
	}

	if (balance == BALANCE::EQUAL) {

		if (OldBalance == BALANCE::SAN) {
			if (BlendRate <= 1) {

				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, 1.0f - BlendRate);
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
				BlendRate += 0.01f;
				MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
				MV1SetAttachAnimTime(BalanceHandle, 1, BlendRate);
			}
			else {
				BlendRate > 0 ? BlendRate -= 0.01f : BlendRate = 0;
			}
		}
		else if (OldBalance == BALANCE::LKA) {
			if (BlendRate <= 1) {
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, 1.0f - BlendRate);
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
				BlendRate += 0.01f;
				MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
				MV1SetAttachAnimTime(BalanceHandle, 2, BlendRate);
			}
			else {
				BlendRate > 0 ? BlendRate -= 0.01f : BlendRate = 0;
			}
		}
		else if (OldBalance == BALANCE::EQUAL) {

		}
	}
	else if (balance == BALANCE::SAN) {
		if (BlendRate <= 1) {

			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, BlendRate);
			BlendRate += 0.01f;
			MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
			MV1SetAttachAnimTime(BalanceHandle, 1, BlendRate);
		}
		else {
			BlendRate > 0 ? BlendRate -= 0.01f : BlendRate = 0;
		}
	}
	else if (balance == BALANCE::LKA) {
		if (BlendRate <= 1) {
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, BlendRate);
			BlendRate += 0.01f;
			MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
			MV1SetAttachAnimTime(BalanceHandle, 2, BlendRate);
		}
		else {
			BlendRate > 0 ? BlendRate -= 0.01f : BlendRate = 0;
		}
	}
}

float Gimmick::GetPolyMaxY(MV1_COLL_RESULT_POLY* Dim, int num) {
	float MaxY = FLT_MIN;
	for (auto i = 0; i < num; ++i) {
		for (auto j = 0; j < 3; ++j) {
			if (MaxY < Dim[i].Position[j].y) {
				MaxY = Dim[i].Position[j].y;
			}
		}
	}
	return MaxY;
}

void Gimmick::Render() {

	MV1DrawModel(BalanceHandle);
	//DrawFormatString(0, 220, GetColor(0, 0, 0), "SanHitFrag = %d", SanHitFlag);
}

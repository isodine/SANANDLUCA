#include "Gimmick.h"


Gimmick::Gimmick() {
	BalanceHandle = MV1LoadModel("res/Balance_MOmarge.mv1");
	SanHitFlag = false;
	LkaHitFlag = false;
	balance = BALANCE::EQUAL;
	AttachAnim1 = MV1AttachAnim(BalanceHandle, 2, -1, FALSE);//水平モーションをアタッチする
	AttachAnimSAN = -1;
	AttachAnimLKA = -1;
	BlendRate = 0;
	BalanceFlag = false;
}

void Gimmick::Initialize()
{
	MV1SetPosition(BalanceHandle, VGet(-80.0f, 200.0f, 210.0f));
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

	MV1_COLL_RESULT_POLY_DIM hitPolyDim1;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim2;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim3;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim4;

	MV1_COLL_RESULT_POLY hitPoly1;
	// サンの腰位置から下方向への直線とサンの皿
	hitPoly1 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(SanPos, VGet(0, 60.f, 0)), VAdd(SanPos, VGet(0, -99999.f, 0)));

	MV1_COLL_RESULT_POLY hitPoly2;
	// ルカの腰位置から下方向への直線とサンの皿
	hitPoly2 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(LkaPos, VGet(0, 60.f, 0)), VAdd(LkaPos, VGet(0, -99999.f, 0)));

	MV1_COLL_RESULT_POLY hitPoly3;
	// サンの腰位置から下方向への直線とルカの皿
	hitPoly3 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(SanPos, VGet(0, 60.f, 0)), VAdd(SanPos, VGet(0, -99999.f, 0)));

	MV1_COLL_RESULT_POLY hitPoly4;
	// ルカの腰位置から下方向への直線とルカの皿
	hitPoly4 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(LkaPos, VGet(0, 60.f, 0)), VAdd(LkaPos, VGet(0, -99999.f, 0)));

	hitPolyDim1 = MV1CollCheck_Capsule(BalanceHandle, 3,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);  //サンがサンの皿に乗ったとき
	hitPolyDim2 = MV1CollCheck_Capsule(BalanceHandle, 4,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);  //ルカがルカの皿に乗ったとき
	hitPolyDim3 = MV1CollCheck_Capsule(BalanceHandle, 3,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);  //ルカがサンの皿に乗ったとき
	hitPolyDim4 = MV1CollCheck_Capsule(BalanceHandle, 4,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);  //サンがルカの皿に乗ったとき

	if (hitPolyDim1.HitNum >= 1) {
		SanHitFlag = true;
		san->vPos = san->vPos;
	}
	else {
		SanHitFlag = false;
	}

	if(hitPolyDim2.HitNum >= 1) {
		LkaHitFlag = true;
		lka->vPos = lka->vPos;
	}
	else {
		LkaHitFlag = false;
	}

	if (hitPolyDim3.HitNum >= 1) {
		LkaHitFlag = true;
		lka->vPos = lka->vPos;
	}
	else {
		LkaHitFlag = false;
	}

	if (hitPolyDim4.HitNum >= 1) {
		LkaHitFlag = true;
		san->vPos = san->vPos;
	}
	else {
		LkaHitFlag = false;
	}

	if ((SanHitFlag == false && LkaHitFlag == false) || (SanHitFlag == true && LkaHitFlag == true)) {
		balance = BALANCE::EQUAL;
		BalanceFlag = true;
	}
	else if (SanHitFlag == true && LkaHitFlag == false) {
		balance = BALANCE::SAN;
		BalanceFlag = true;
	}
	else if (SanHitFlag == false && LkaHitFlag == true) {
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
		if (BlendRate == 1) {
			BlendRate = 0;
		}
		// ステータスに合わせてアニメーションをアタッチする
		switch (balance) {
		case BALANCE::EQUAL:
			AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
			if (oldBalance == BALANCE::SAN) {
				AttachAnimSAN = MV1AttachAnim(BalanceHandle, 1, -1, FALSE);//左傾きモーションをアタッチする
			}
			else if(oldBalance == BALANCE::LKA) {
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

	if (balance == BALANCE::EQUAL) {
		
		if (oldBalance == BALANCE::SAN) {
			if (BlendRate >= 1) {
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, 1.0f - BlendRate);
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
				BlendRate += 0.01f;
			}
		}
		else if (oldBalance == BALANCE::LKA) {
			if (BlendRate >= 1) {
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, 1.0f - BlendRate);
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
				BlendRate += 0.01f;
			}
		}
		else if (oldBalance == BALANCE::EQUAL) {

		}
	}
	else if (balance == BALANCE::SAN) {
		if (BlendRate >= 1) {
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, BlendRate);
			BlendRate += 0.01f;
		}
	}
	else if (balance == BALANCE::LKA) {
		if (BlendRate >= 1) {
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, BlendRate);
			BlendRate += 0.01f;
		}
	}
	if (BlendRate == 1) {
		BlendRate = 0;
	}
	MV1CollResultPolyDimTerminate(hitPolyDim1);
	MV1CollResultPolyDimTerminate(hitPolyDim2);
	MV1CollResultPolyDimTerminate(hitPolyDim3);
	MV1CollResultPolyDimTerminate(hitPolyDim4);
}



void Gimmick::Render() {
	MV1SetPosition(BalanceHandle, VGet(-80.0f, 200.0f, 210.0f));
	MV1DrawModel(BalanceHandle);
	DrawFormatString(0, 220, GetColor(0, 0, 0), "SanHitFrag = %d", SanHitFlag);
}

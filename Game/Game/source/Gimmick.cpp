#include "Gimmick.h"


Gimmick::Gimmick() {
	BalanceHandle = MV1LoadModel("res/Balance_MOmarge.mv1");
	SanHitFlag = false;
	LkaHitFlag = false;
	balance = BALANCE::EQUAL;
	AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
	AttachAnimSAN = -1;
	AttachAnimLKA = -1;
	BlendRate = 0;
	BalanceFlag = false;
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

	MV1_COLL_RESULT_POLY_DIM hitPolyDim1;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim2;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim3;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim4;

	MV1_COLL_RESULT_POLY hitPoly1;
	MV1_COLL_RESULT_POLY hitPoly2;
	MV1_COLL_RESULT_POLY hitPoly3;
	MV1_COLL_RESULT_POLY hitPoly4;
	
	
	hitPolyDim1 = MV1CollCheck_Capsule(BalanceHandle, 3,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);  //サンがサンの皿に乗ったとき
	hitPolyDim2 = MV1CollCheck_Capsule(BalanceHandle, 4,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);  //ルカがルカの皿に乗ったとき
	hitPolyDim3 = MV1CollCheck_Capsule(BalanceHandle, 3,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);  //ルカがサンの皿に乗ったとき
	hitPolyDim4 = MV1CollCheck_Capsule(BalanceHandle, 4,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);  //サンがルカの皿に乗ったとき

	hitPoly1 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(san->vPos, VGet(0, san->_colSubY, 0)), VAdd(san->vPos, VGet(0, -99999.f, 0)));
	hitPoly2 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(lka->vPos, VGet(0, lka->_colSubY, 0)), VAdd(lka->vPos, VGet(0, -99999.f, 0)));
	hitPoly3 = MV1CollCheck_Line(BalanceHandle, 3,
		VAdd(lka->vPos, VGet(0, lka->_colSubY, 0)), VAdd(lka->vPos, VGet(0, -99999.f, 0)));
	hitPoly4 = MV1CollCheck_Line(BalanceHandle, 4,
		VAdd(san->vPos, VGet(0, san->_colSubY, 0)), VAdd(san->vPos, VGet(0, -99999.f, 0)));

	if (hitPoly1.HitFlag) {
		SanHitFlag = true;
		san->vPos.y = hitPoly1.HitPosition.y - 0.01;
		san->throughtime = 0;
	}
	//hitPolyDim1.Dim->HitPosition.y
	else {
		SanHitFlag = false;
	}

	if (hitPoly2.HitFlag) {
		LkaHitFlag = true;
		lka->vPos.y = hitPoly2.HitPosition.y - 0.01;
		lka->throughtime = 0;
	}
	else {
		LkaHitFlag = false;
	}

	if (hitPoly3.HitFlag) {
		SanHitFlag = true;
		lka->vPos.y = hitPoly3.HitPosition.y - 0.01;
		lka->throughtime = 0;
	}
	else {
		SanHitFlag = false;
	}

	if (hitPoly4.HitFlag) {
		LkaHitFlag = true;
		san->vPos.y = hitPoly4.HitPosition.y - 0.01;
		san->throughtime = 0;
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
		/*if (BlendRate == 1) {
			BlendRate = 0;
		}*/
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
			if (BlendRate <= 1) {
				
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, 1.0f - BlendRate);
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
				BlendRate += 0.001f;
				MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
				MV1SetAttachAnimTime(BalanceHandle, 1, BlendRate);
			}
			else {
				BlendRate > 0 ? BlendRate -= 0.001f : BlendRate = 0;
			}
		}
		else if (oldBalance == BALANCE::LKA) {
			if (BlendRate <= 1) {
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, 1.0f - BlendRate);
				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
				BlendRate += 0.001f;
			}
			else {
				BlendRate >0?BlendRate -= 0.001f: BlendRate = 0;
			}
		}
		else if (oldBalance == BALANCE::EQUAL) {

		}
	}
	else if (balance == BALANCE::SAN) {
		if (BlendRate <= 1) {
			
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, BlendRate);
			BlendRate += 0.001f;
			MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
			MV1SetAttachAnimTime(BalanceHandle, 1, BlendRate);
		}
		else {
			BlendRate > 0 ? BlendRate -= 0.001f : BlendRate = 0;
		}
	}
	else if (balance == BALANCE::LKA) {
		if (BlendRate <= 1) {
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, BlendRate);
			BlendRate += 0.001f;
		}
		else {
			BlendRate > 0 ? BlendRate -= 0.001f : BlendRate = 0;
		}
	}
	/*if (BlendRate == 1) {
		BlendRate = 0;
	}*/

	

	/*MV1CollResultPolyDimTerminate(hitPolyDim1);
	MV1CollResultPolyDimTerminate(hitPolyDim2);
	MV1CollResultPolyDimTerminate(hitPolyDim3);
	MV1CollResultPolyDimTerminate(hitPolyDim4);*/
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

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

	SANDisk = MV1GetFramePosition(BalanceHandle, 26);
	LKADisk = MV1GetFramePosition(BalanceHandle, 25);

	MV1RefreshCollInfo(BalanceHandle, 3, 8);  //サンの皿
	MV1RefreshCollInfo(BalanceHandle, 4, 8);  //ルカの皿

	BALANCE oldBalance = balance;

	if (balance != oldBalance) {
		EnumFlag = true;
	}

	if (EnumFlag) {
		oldBalance = balance;
		EnumFlag = false;
	}

	switch (balance)
	{
	case Gimmick::BALANCE::SAN:
		BalancePer -= 0.01;
		if (BalancePer < -1) {
			BalancePer = -1;
		}
		break;
	case Gimmick::BALANCE::LKA:
		BalancePer += 0.01;
		if (BalancePer > 1) {
			BalancePer = 1;
		}
		break;
	case Gimmick::BALANCE::EQUAL:
	case Gimmick::BALANCE::NONE:
		if (BalancePer >= 0) {
			BalancePer -= 0.01;
			if (BalancePer <= 0) {
				BalancePer = 0;
			}
		}
		else {
			BalancePer += 0.01;
			if (BalancePer >= 0) {
				BalancePer = 0;
			}
			break;
		}
	}
		BlendRate = abs(BalancePer);
		

		hitPolyDimSAN = MV1CollCheck_Capsule(BalanceHandle, 3,
			VGet(san->vPos.x, san->vPos.y + 30, san->vPos.z), VGet(san->vPos.x, san->vPos.y + 75, san->vPos.z), 30.0f);


		hitPoly1 = MV1CollCheck_Line(BalanceHandle, 3,
			VAdd(san->vPos, VGet(0, 1000, 0)), VAdd(san->vPos, VGet(0, -1000.f, 0)));
		hitPoly2 = MV1CollCheck_Line(BalanceHandle, 4,
			VAdd(lka->vPos, VGet(0, 1000, 0)), VAdd(lka->vPos, VGet(0, -1000.f, 0)));
		hitPoly3 = MV1CollCheck_Line(BalanceHandle, 3,
			VAdd(lka->vPos, VGet(0, 1000, 0)), VAdd(lka->vPos, VGet(0, -1000.f, 0)));
		hitPoly4 = MV1CollCheck_Line(BalanceHandle, 4,
			VAdd(san->vPos, VGet(0, 1000, 0)), VAdd(san->vPos, VGet(0, -1000.f, 0)));
		//toDoプレイヤーが浮くバグあり
		if (hitPoly1.HitFlag || hitPoly3.HitFlag) {
			if (hitPoly1.HitFlag) {
				SanHitFlag = true;
			}
			else {
				SanHitFlag = true;
			}
		}
		else {
			SanHitFlag = false;
		}

		if (hitPoly2.HitFlag || hitPoly4.HitFlag) {
			if (hitPoly2.HitFlag) {
				LkaHitFlag = true;
			}
			else {
				LkaHitFlag = true;
			}
		}
		else {
			LkaHitFlag = false;
		}

		if ((SanHitFlag == true && LkaHitFlag == true)) {
			balance = BALANCE::EQUAL;
			if (oldBalance != balance) {
				BalanceFlag = true;
			}
		}
		else if (SanHitFlag == false && LkaHitFlag == false) {
			balance = BALANCE::NONE;
			if (oldBalance != balance) {
				BalanceFlag = true;
			}
		}
		else if (SanHitFlag == true && LkaHitFlag == false) {
			balance = BALANCE::SAN;
			if (oldBalance != balance) {
				BalanceFlag = true;
			}
		}
		else if (SanHitFlag == false && LkaHitFlag == true) {
			balance = BALANCE::LKA;
			if (oldBalance != balance) {
				BalanceFlag = true;
			}
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
			case BALANCE::NONE:
				AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
				if (oldBalance == BALANCE::SAN) {
					AttachAnimSAN = MV1AttachAnim(BalanceHandle, 1, -1, FALSE);//左傾きモーションをアタッチする
				}
				else if (oldBalance == BALANCE::LKA) {
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
			//BlendRate = 0;
			BalanceFlag = false;
		}
		else {
			//BalanceFlag = false;
		}
			
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - abs(BalancePer));
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, abs(min(BalancePer, 0.0)));
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, max(BalancePer, 0.0));
		MV1SetAttachAnimTime(BalanceHandle, 0, abs(BalancePer));
		MV1SetAttachAnimTime(BalanceHandle, 1, abs(BalancePer));
		if (balance == BALANCE::SAN) {
			/*san->Landing(SANDisk.y - 275);*/
			}
		else if (balance == BALANCE::LKA) {
			/*lka->Landing(LKADisk.y - 275);*/
		}
		else if (balance == BALANCE::EQUAL) {
			/*san->Landing(SANDisk.y - 275);
			lka->Landing(LKADisk.y - 275);*/
		}
		else if (balance == BALANCE::NONE) {
			/*san->Landing(SANDisk.y - 280);
			lka->Landing(LKADisk.y - 280);*/
		}
				
			

	//	if (balance == BALANCE::EQUAL) {
	//		if (oldBalance == BALANCE::SAN) {
	//			if (true) {

	//				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, 1.0f - BlendRate);
	//				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
	//				san->Landing(SANDisk.y - 280);
	//				lka->Landing(LKADisk.y - 280);
	//				//BlendRate += 0.01f;
	//				MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
	//				MV1SetAttachAnimTime(BalanceHandle, 1, BlendRate);
	//			}
	//			//todoここのelseに入らない
	//			else {
	//				//BlendRate = 0;
	//				BalanceFlag = false;
	//			}
	//		}
	//		else if (oldBalance == BALANCE::LKA) {
	//			if (true) {
	//				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, 1.0f - BlendRate);
	//				MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, BlendRate);
	//				san->Landing(SANDisk.y - 280);
	//				lka->Landing(LKADisk.y - 280);
	//				//BlendRate += 0.01f;
	//				MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
	//				MV1SetAttachAnimTime(BalanceHandle, 2, BlendRate);
	//			}
	//			else {
	//				//BlendRate > 0 ? BlendRate -= 0.01f : BlendRate = 0;
	//				BalanceFlag = false;
	//			}
	//		}
	//		/*else if (oldBalance == BALANCE::EQUAL) {

	//		}*/
	//	}
	//	else if (balance == BALANCE::SAN) {
	//		if (true) {
	//			//san->Landing(hitPoly1.HitPosition.y);
	//			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
	//			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, BlendRate);
	//			san->Landing(SANDisk.y - 280);
	//			//BlendRate += 0.01f;
	//			MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
	//			MV1SetAttachAnimTime(BalanceHandle, 1, BlendRate);
	//		}
	//		else {
	//			//BlendRate = 0;
	//			BalanceFlag = false;
	//		}
	//	}
	//	else if (balance == BALANCE::LKA) {
	//		if (true) {
	//			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
	//			MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, BlendRate);
	//			lka->Landing(LKADisk.y - 280);
	//			//BlendRate += 0.01f;
	//			MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
	//			MV1SetAttachAnimTime(BalanceHandle, 2, BlendRate);
	//		}
	//		else {
	//			//BlendRate = 0;
	//			BalanceFlag = false;
	//		}
	//	}
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

#include "Gimmick.h"


Gimmick::Gimmick() {
	BalanceHandle = MV1LoadModel("res/Balance/Motion/Balance_GEONew.mv1");
	SanHandle = MV1LoadModel("res/Balance/Motion/Balance_San.mv1");
	LkaHandle = MV1LoadModel("res/Balance/Motion/Balance_Lka.mv1");
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
	MV1SetPosition(BalanceHandle, VGet(0.f, 700.0f, 7600.f));
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
		

		
		//toDoプレイヤーが浮くバグあり
		

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
			BalanceFlag = false;
		}
		else {

		}
			
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - abs(BalancePer));
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, abs(min(BalancePer, 0.0)));
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, max(BalancePer, 0.0));
		MV1SetAttachAnimTime(BalanceHandle, 0, abs(BalancePer));
		MV1SetAttachAnimTime(BalanceHandle, 1, abs(BalancePer));
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
	MV1SetPosition(BalanceHandle, VGet(50.0f, 700.0f, 7650.0f));
	MV1DrawModel(BalanceHandle);
}

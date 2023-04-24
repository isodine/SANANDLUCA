/*****************************************************************//**
 * \file   Gimmick.cpp
 * \brief  天秤の動作全般
 * 
 * \author 土屋　涼乃
 * \date   December 2022
 *********************************************************************/
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
}

void Gimmick::Initialize()
{
	MV1SetPosition(BalanceHandle, VGet(0.f, 700.0f, 7600.f));
	MV1SetupCollInfo(BalanceHandle, 3, 8, 8, 8);  //サンの皿
	MV1SetupCollInfo(BalanceHandle, 4, 8, 8, 8);  //ルカの皿

}

void Gimmick::Terminate() {
	MV1DeleteModel(BalanceHandle);
	MV1TerminateCollInfo(BalanceHandle, 3);
	MV1TerminateCollInfo(BalanceHandle, 4);
}

void Gimmick::Process() {

}

void Gimmick::Balance(VECTOR SanPos, VECTOR LkaPos) {

	//天秤の皿の上の位置（プレイヤーの動きのため）の取得
	SANDisk = MV1GetFramePosition(BalanceHandle, 26);
	LKADisk = MV1GetFramePosition(BalanceHandle, 25);

	

	BALANCE oldBalance = balance;

	if (EnumFlag) {
		oldBalance = balance;
	}

	//タイプによって傾く向きを変える（モーションのブレンド率が変わる）
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
	    //モーションのブレンド率を決定している
		BlendRate = abs(BalancePer);
		

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
		
		//タイプに応じてもしょんをブレンド率に応じてブレンドする
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - abs(BalancePer));
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, abs(min(BalancePer, 0.0)));
		MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimLKA, max(BalancePer, 0.0));
		MV1SetAttachAnimTime(BalanceHandle, 0, abs(BalancePer));
		MV1SetAttachAnimTime(BalanceHandle, 1, abs(BalancePer));
	}



void Gimmick::Render() {
	MV1SetPosition(BalanceHandle, VGet(50.0f, 700.0f, 7650.0f));
	MV1DrawModel(BalanceHandle);
}

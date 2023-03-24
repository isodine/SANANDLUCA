#include "Damage.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "time.h"
#include "Include.h"
//#include "ModeGame.h"


Damage::Damage() {

}

Damage::~Damage() {

}

void Damage::SetGame(ModeGame* game) {
	Game = game;
}

void Damage::Initialize(SAN* san, LKA* lka) {
	San = san;
	Lka = lka;
  
	SanHP = 6;
	LkaHP = 6;

	MaxSanHP = 6;
	MaxLkaHP = 6;

	Distance = 1000;

	SanCoolTime = 0;
	LkaCoolTime = 0;

	SanHitFlag = false;
	LkaHitFlag = false;

	stageFlag = true;
	stageHandle = san->stageHandle;
}

void Damage::Terminate() {

}

void Damage::Process() {

	//San->DamageProcess();
	//Lka->DamageProcess();

	Distance = VSize(VSub(VGet(Lka->vPos.x, Lka->vPos.y + 50, Lka->vPos.z), VGet(San->vPos.x, San->vPos.y + 50, San->vPos.z)));

	if (Distance < 85 && SanHitFlag == false && LkaHitFlag == false) {
		San->HP -= 2;
		Lka->HP -= 2;
		SanHitFlag = true;
		LkaHitFlag = true;
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
	}
	else if (Distance < 110 && Distance >= 85 && SanHitFlag == false && LkaHitFlag == false) {
		San->HP -= 1;
		Lka->HP -= 1;
		SanHitFlag = true;
		LkaHitFlag = true;
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
	}


	if (stageFlag == true) {
		MV1_COLL_RESULT_POLY_DIM HitPolySan;
		MV1_COLL_RESULT_POLY_DIM HitPolyLka;
		HitPolySan = MV1CollCheck_Capsule(Game->_handleMap, 3, VGet(San->vPos.x, San->vPos.y + 30, San->vPos.z), VGet(San->vPos.x, San->vPos.y + 75, San->vPos.z), 30.0f);
		HitPolyLka = MV1CollCheck_Capsule(Game->_handleMap, 2, VGet(Lka->vPos.x, Lka->vPos.y + 30, Lka->vPos.z), VGet(Lka->vPos.x, Lka->vPos.y + 75, Lka->vPos.z), 30.0f);

		if ((HitPolySan.HitNum >= 1) && !SanHitFlag) {
			San->HP -= 1;
			SanHitFlag = true;
			PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
		}

		if ((HitPolyLka.HitNum >= 1) && !LkaHitFlag) {
			Lka->HP -= 1;
			LkaHitFlag = true;
			PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
		}
	}

	

	if (SanHitFlag == true) {
		SanCoolTime += 1;
	}

	if (LkaHitFlag == true) {
		LkaCoolTime += 1;
	}

	if (SanCoolTime >= 60) {
		SanHitFlag = false;
		SanCoolTime = 0;
	}

	if (LkaCoolTime >= 60) {
		LkaHitFlag = false;
		LkaCoolTime = 0;
	}
}

void Damage::Render() {
	DrawFormatString(0, 200, GetColor(0, 0, 0), "San %d", SanHP);
	DrawFormatString(0, 220, GetColor(0, 0, 0), "Lka %d", LkaHP);
	DrawFormatString(0, 240, GetColor(0, 0, 0), "Distance %f", Distance);

	auto vec1 = VGet(Lka->vPos.x, Lka->vPos.y + 50, Lka->vPos.z);
	auto vec2 = VGet(San->vPos.x, San->vPos.y + 50, San->vPos.z);


	DrawFormatString(0, 260, GetColor(0, 0, 0), "%f, %f, %f", vec1.x, vec1.y, vec1.z);
	DrawFormatString(0, 280, GetColor(0, 0, 0), "%f, %f, %f", vec2.x, vec2.y, vec2.z);

	DrawFormatString(0, 300, GetColor(0, 0, 0), "SanCoolTime %f", SanCoolTime);
	DrawFormatString(0, 320, GetColor(0, 0, 0), "LkaCoolTime %f", LkaCoolTime);

	DrawFormatString(0, 340, GetColor(0, 0, 0), "SanHitFlag %d", SanHitFlag);
	DrawFormatString(0, 360, GetColor(0, 0, 0), "LkaHitFlag %d", LkaHitFlag);

	DrawCapsule3D(VGet(San->vPos.x, San->vPos.y + 30, San->vPos.z), VGet(San->vPos.x, San->vPos.y + 75, San->vPos.z), 30.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
	DrawCapsule3D(VGet(Lka->vPos.x, Lka->vPos.y + 30, Lka->vPos.z), VGet(Lka->vPos.x, Lka->vPos.y + 75, Lka->vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);

}

void Damage::SwampColl(std::vector<std::unique_ptr<BossSwamp>>& swamps)
{
	for (int i = 0; i < swamps.size(); i++)
	{
		MV1_COLL_RESULT_POLY_DIM HitPolySwamp;

		swamps[i]->isSan ? HitPolySwamp = MV1CollCheck_Capsule(swamps[i]->handle, 3,
			VGet(San->vPos.x, San->vPos.y + 30, San->vPos.z), VGet(San->vPos.x, San->vPos.y + 75, San->vPos.z), 30.0f) :
			HitPolySwamp = MV1CollCheck_Capsule(swamps[i]->handle, 3,
				VGet(Lka->vPos.x, Lka->vPos.y + 30, Lka->vPos.z), VGet(Lka->vPos.x, Lka->vPos.y + 75, Lka->vPos.z), 30.0f);

		if (!swamps[i]->isSan)
		{
			HitPolySwamp = MV1CollCheck_Capsule(swamps[i]->handle, swamps[i]->handleCol,
				VGet(San->vPos.x, San->vPos.y + 30, San->vPos.z), VGet(San->vPos.x, San->vPos.y + 75, San->vPos.z), 30.0f);
			if ((HitPolySwamp.HitNum >= 1) && !SanHitFlag) {
				San->HP -= 1;
				SanHitFlag = true;
				PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
			}
		}
		if (swamps[i]->isSan)
		{
			HitPolySwamp = MV1CollCheck_Capsule(swamps[i]->handle, swamps[i]->handleCol,
				VGet(Lka->vPos.x, Lka->vPos.y + 30, Lka->vPos.z), VGet(Lka->vPos.x, Lka->vPos.y + 75, Lka->vPos.z), 30.0f);
			if ((HitPolySwamp.HitNum >= 1) && !LkaHitFlag) {
				Lka->HP -= 1;
				LkaHitFlag = true;
				PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
			}
		}
		//swamps[i]->Update(swamps);
	}
}
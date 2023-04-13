#include "Damage.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "time.h"
//#include "ModeGame.h"


Damage::Damage() {

}

Damage::~Damage() {

}

void Damage::SetBomb(SanBomb* sanbomb, LkaBomb* lkabomb) {
	Sanbomb = sanbomb;
	Lkabomb = lkabomb;
}


void Damage::Initialize(SAN* san, LKA* lka) {
	San = san;
	Lka = lka;
  
	Distance = 1000;

	SanCoolTime = 0;
	LkaCoolTime = 0;

	SanHitFlag = false;
	LkaHitFlag = false;
	SanFloorHitFlag = false;
	LkaFloorHitFlag = false;
	SanSlimeHitFlag = false;
	LkaSlimeHitFlag = false;

	stageHandle = san->stageHandle;

	MV1SetupCollInfo(San->Mhandle, 3, 8, 8, 8);
	MV1SetupCollInfo(Lka->Mhandle, 8, 8, 8, 8);
}

void Damage::Terminate() {
	MV1TerminateCollInfo(San->Mhandle, 3);
	MV1TerminateCollInfo(Lka->Mhandle, 8);
}

void Damage::Process() {
	MV1RefreshCollInfo(San->Mhandle, 3);
	MV1RefreshCollInfo(Lka->Mhandle, 8);

	HitPolySanBomb = MV1CollCheck_Sphere(Lka->Mhandle, 8, Sanbomb->vPos, Sanbomb->sphereSize);
	HitPolyLkaBomb = MV1CollCheck_Sphere(San->Mhandle, 3, Lkabomb->vPos, Lkabomb->sphereSize);

	Distance = VSize(VSub(VGet(Lka->vPos.x, Lka->vPos.y + 50, Lka->vPos.z), VGet(San->vPos.x, San->vPos.y + 50, San->vPos.z)));

	if (Distance < 85 && SanHitFlag == false && LkaHitFlag == false) {
		San->HP -= 2;
		Lka->HP -= 2;
		SanHitFlag = true;
		LkaHitFlag = true;
		San->sanBackFlag = true;
		Lka->lkaBackFlag = true;
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 300, -1);
		StartJoypadVibration(DX_INPUT_PAD2, 1000, 300, -1);
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundFile("res/06_Sound/03_SE/san_lka_damege.mp3", DX_PLAYTYPE_BACK);
	}
	else if (Distance < 110 && Distance >= 85 && SanHitFlag == false && LkaHitFlag == false) {
		San->HP -= 1;
		Lka->HP -= 1;
		San->sanBackFlag = true;
		Lka->lkaBackFlag = true;
		SanHitFlag = true;
		LkaHitFlag = true;
		StartJoypadVibration(DX_INPUT_PAD1, 1000, 300, -1);
		StartJoypadVibration(DX_INPUT_PAD2, 1000, 300, -1);
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundFile("res/06_Sound/03_SE/san_lka_damege.mp3", DX_PLAYTYPE_BACK); 		PlaySoundFile("res/06_Sound/03_SE/san_lka_damege.mp3", DX_PLAYTYPE_BACK);
		PlaySoundFile("res/06_Sound/03_SE/san_lka_damege.mp3", DX_PLAYTYPE_BACK);
	}
	if ((HitPolyLkaBomb.HitNum >= 1) && !SanHitFlag) {
		San->HP -= 1;
		SanHitFlag = true;
		StartJoypadVibration(DX_INPUT_PAD1, 750, 300, -1);
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
	}

	if ((HitPolySanBomb.HitNum >= 1) && !LkaHitFlag) {
		Lka->HP -= 1;
		LkaHitFlag = true;
		StartJoypadVibration(DX_INPUT_PAD2, 750, 300, -1);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
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

void Damage::SlimeDamage(std::vector<std::unique_ptr<Slime>>& slimes) {
	if (slimes[0]->lkaHitFlag && !LkaSlimeHitFlag) {
		Lka->HP -= 1;
		LkaSlimeHitFlag = true;
		StartJoypadVibration(DX_INPUT_PAD2, 750, 300, -1);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
	}
	if (slimes[1]->sanHitFlag && !SanSlimeHitFlag) {
		San->HP -= 1;
		SanSlimeHitFlag = true;
		StartJoypadVibration(DX_INPUT_PAD1, 750, 300, -1);
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
	}
	if (SanSlimeHitFlag == true) {
		SanCoolTime += 1;
	}

	if (LkaSlimeHitFlag == true) {
		LkaCoolTime += 1;
	}

	if (SanCoolTime >= 120) {
		SanSlimeHitFlag = false;
		SanCoolTime = 0;
	}

	if (LkaCoolTime >= 120) {
		LkaSlimeHitFlag = false;
		LkaCoolTime = 0;
	}
}

void Damage::StageDamage(int StageHandle) {
	HitPolySan = MV1CollCheck_Capsule(StageHandle, 3, VGet(San->vPos.x, San->vPos.y + 30, San->vPos.z), VGet(San->vPos.x, San->vPos.y + 75, San->vPos.z), 30.0f);
	HitPolyLka = MV1CollCheck_Capsule(StageHandle, 2, VGet(Lka->vPos.x, Lka->vPos.y + 30, Lka->vPos.z), VGet(Lka->vPos.x, Lka->vPos.y + 75, Lka->vPos.z), 30.0f);

	if ((HitPolySan.HitNum >= 1) && !SanFloorHitFlag) {
		San->HP -= 1;
		SanFloorHitFlag = true;
		StartJoypadVibration(DX_INPUT_PAD1, 750, 300, -1);
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
	}

	if ((HitPolyLka.HitNum >= 1) && !LkaFloorHitFlag) {
		Lka->HP -= 1;
		LkaFloorHitFlag = true;
		StartJoypadVibration(DX_INPUT_PAD2, 750, 300, -1);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
	}

	if (SanFloorHitFlag == true) {
		SanCoolTime += 1;
	}

	if (LkaFloorHitFlag == true) {
		LkaCoolTime += 1;
	}

	if (SanCoolTime >= 60) {
		SanFloorHitFlag = false;
		SanCoolTime = 0;
	}

	if (LkaCoolTime >= 60) {
		LkaFloorHitFlag = false;
		LkaCoolTime = 0;
	}
}

void Damage::Render() {
#ifdef debug
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
#endif

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
				San->HP -= 1;;
				SanHitFlag = true;
				StartJoypadVibration(DX_INPUT_PAD1, 750, 1, -1);
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
				StartJoypadVibration(DX_INPUT_PAD2, 750, 1, -1);
				PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
			}
		}
		//swamps[i]->Update(swamps);
	}
}
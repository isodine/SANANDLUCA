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

//void Damage::SetGame(ModeGame* game) {
//	Game = game;
//}

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
		PlaySoundFile("res/06_Sound/03_SE/san_lka_damege.mp3", DX_PLAYTYPE_BACK);
	}
	else if (Distance < 110 && Distance >= 85 && SanHitFlag == false && LkaHitFlag == false) {
		San->HP -= 1;
		Lka->HP -= 1;
		SanHitFlag = true;
		LkaHitFlag = true;
		PlaySoundMem(VOICEdamageSAN[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundMem(VOICEdamageLKA[GetRand(1)], DX_PLAYTYPE_BACK, true);
		PlaySoundFile("res/06_Sound/03_SE/san_lka_damege.mp3", DX_PLAYTYPE_BACK); 1;
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
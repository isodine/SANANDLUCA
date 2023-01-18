#include "Damage.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include"LKAclass.h"
#include"SANclass.h"
#include "ModeGame.h"


void Damage::Initialize() {
	SanHP = 100;
	LkaHP = 100;

	Distance = 1000;

	SanHitFlag = false;
	LkaHitFlag = false;

}

void Damage::Terminate() {
	
}

void Damage::Process() {
	
	Distance = VSize(VSub(san.vPos, lka.vPos));

	if (Distance < 70 && SanHitFlag == false && LkaHitFlag == false) {
		SanHP -= 2;
		LkaHP -= 2;
		SanHitFlag = true;
		LkaHitFlag = true;
	}
	else if (Distance < 110 && SanHitFlag == false && LkaHitFlag == false) {
		SanHP -= 1;
		LkaHP -= 1;
		SanHitFlag = true;
		LkaHitFlag = true;
	}
	
}

void Damage::Render() {
	DrawFormatString(0, 100, GetColor(0, 0, 255), "San %d", SanHP);
	DrawFormatString(0, 120, GetColor(0, 0, 255), "Lka %d", LkaHP);

}
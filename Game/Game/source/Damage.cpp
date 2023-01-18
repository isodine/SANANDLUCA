#include "Damage.h"
#include "AppFrame.h"
#include "ApplicationMain.h"


Damage::Damage() {
	
}

Damage::~Damage() {

}

void Damage::Initialize() {

	San.Initialize();
	Lka.Initialize();

	SanHP = 100;
	LkaHP = 100;

	Distance = 1000;

	SanHitFlag = false;
	LkaHitFlag = false;

}

void Damage::Terminate() {
	
}

void Damage::Process() {
	
	Distance = VSize(VSub(San.vPos, Lka.vPos));

	if (Distance < 70 && SanHitFlag == false && LkaHitFlag == false) {
		SanHP -= 2;
		LkaHP -= 2;
		SanHitFlag = true;
		LkaHitFlag = true;
	}
	else if (Distance < 110 && Distance >= 70 && SanHitFlag == false && LkaHitFlag == false) {
		SanHP -= 1;
		LkaHP -= 1;
		SanHitFlag = true;
		LkaHitFlag = true;
	}
	
}

void Damage::Render() {
	DrawFormatString(0, 200, GetColor(255, 255, 255), "San %d", SanHP);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "Lka %d", LkaHP);

}
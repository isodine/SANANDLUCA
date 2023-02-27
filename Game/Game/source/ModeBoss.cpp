#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeBoss.h"
#include "ModeEnding.h"
#include "ModeGameOver.h"


bool ModeBoss::Initialize() {
	if (!base::Initialize()) { return false; }
	boss.Initialize();
	StageHandle = MV1LoadModel("res/07_stage_map/Boss_Stage/04_Stage_Boss.mv1");
	_vPos = VGet(1000, 1000, 0);
	_vTarget = VGet(1000, 0, 1000);
	_clipNear = 10;
	_clipFar = 2000;
	frameMapCollisionwall = 1;
	frameMapCollisionfloor = 0;
	SetCameraPositionAndTarget_UpVecY(_vPos, _vTarget);
	SetCameraNearFar(_clipNear, _clipFar);
	san.Initialize();
	lka.Initialize();

	GameMode = 3;
	san.SetCamera(&_cam);
	san.SetBomb(&sanbomb);
	san.SetDamage(&damage);
	lka.SetCamera(&_cam);
	lka.SetBomb(&sanbomb);
	lka.SetDamage(&damage);
	damage.Initialize(&san, &lka);
	san.vPos = VGet(900, 20, 900);
	lka.vPos = VGet(1100, 20, 1100);
	return true;
}

bool ModeBoss::Terminate() {
	base::Terminate();

	return true;
}

bool ModeBoss::Process() {
	base::Process();
	boss.Process();


	damage.Process();
	san.Update();
	lka.Update();

	/*if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeEnding(), 1, "ending");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "GameOver");
	}*/

	return true;
}

bool ModeBoss::Render() {

	SetUseLighting(TRUE);
	SetGlobalAmbientLight(GetColorF(0.1f, 0.1f, 0.1f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 1));
	MV1SetFrameVisible(StageHandle, 1, false);
	DrawString(0, 0, "É{ÉX", GetColor(255, 255, 255));
	MV1SetPosition(StageHandle, VGet(1000,0,1000));
	MV1DrawModel(StageHandle);


 
	boss.Render();
	san.Render();
	lka.Render();
	return true;
}
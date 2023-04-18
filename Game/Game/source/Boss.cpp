#include "SANclass.h"
#include "LKAclass.h"

void Boss::Initialize() {
	model.pos = VGet(0, 60, 750);
	BossDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	model.dir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	StopDir = 0.03;
	StopPos = 200.f;
	TargetDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	rotate = 0;
	rotateFlag = true;
	walkFlag = false;
	SanCatchFlag = false;
	LkaCatchFlag = false;
	sanhitEf = false;
	lkahitEf = false;
	searchFlag = false;
	downFlag = false;
	bossdownEf = false;
	walkTimeCount = 0;
	walkRand = 0;
	CrushCount = 0;
	PullCount = 0;
	WaitCount = 0;
	IdleCount = 0;
	CaptureCount = 0;
	EndCount = 0;
	DownCount = 0;
	BossHP = 100;
	BossMaxHP = 100;
	SwampCnt = 3;
	BossPosition0 = VGet(41, 57, 274);
	BossPosition1 = VGet(-327, 57, 673);
	BossPosition2 = VGet(41, 57, 1013);
	BossPosition3 = VGet(327, 57, 673);

	swampDir = VGet(0, 0, 0);
	swampDegreeDir = swampDir;

	MV1SetupCollInfo(model.modelHandle, 2, 8, 8, 8);
	type = BOSSTYPE::NONE;
	phType = PH::NONE;
	oldphType = PH::NONE;
	acidHandle = LoadGraph("res/Boss/robo_acid_tex.png");
	alkaliHandle = LoadGraph("res/Boss/robo_alcali_tex.png");
	noneHandle = LoadGraph("res/Boss/robo_tex.png");
	HPhandle = LoadGraph("res/BossHP/HP.png");
	iconhandle = LoadGraph("res/BossHP/icon.png");
	BGhandle = LoadGraph("res/BossHP/BG.png");
	flamehandle = LoadGraph("res/BossHP/flame.png");
	BossSuck = LoadSoundMem("res/06_Sound/03_SE/beaker_suck.wav");
	BossSearch = LoadSoundMem("res/06_Sound/03_SE/beaker_search.wav");
	handleBaseSan = MV1LoadModel("res/07_Stage_map/Boss_Stage/acid.mv1");
	handleBaseLka = MV1LoadModel("res/07_Stage_map/Boss_Stage/alkali.mv1");
	//モデルをメモリに読み込んでいる
	manager->modelImport("res/Boss/beaker_robot_All220217.mv1", 1.f, &model);
	//拡大率の適用
	manager->changeScale(&model);
}

void Boss::Terminate() {
	MV1TerminateCollInfo(model.modelHandle, 2);
	MV1DeleteModel(model.modelHandle);

}

void Boss::Process(Damage& damage) {
	MV1RefreshCollInfo(model.modelHandle, 2);
	HandPos = MV1GetFramePosition(model.modelHandle, 3);
	AddPos = VNorm(VSub(MV1GetFramePosition(model.modelHandle, 5), HandPos));
	SphereCenter = VAdd(HandPos, VScale(AddPos, 80));
	BOSSTYPE oldtype = type;

	rotationMatrix = MMult(MMult(MGetRotX(model.dir.x), MGetRotY(model.dir.y)), MGetRotZ(model.dir.z));
	forward = VTransform({ 0.0f,0.0f,-1.0f }, rotationMatrix);

	switch (type) {
	case BOSSTYPE::NONE:
		type = BOSSTYPE::ROTATION;
		break;
	case BOSSTYPE::RUSH:
		Rush(san->vPos, lka->vPos, san->Mhandle, lka->Mhandle, modeboss->_handleMap);
		break;
	case BOSSTYPE::CAPTURE:
		Capture();
		break;
	case BOSSTYPE::CAPTUREEND:
		CaptureEnd();
		break;
	case BOSSTYPE::ROTATION:
		Rotation(san->vPos, lka->vPos);
		break;
	case BOSSTYPE::WALK:
		Walk();
		break;
	case BOSSTYPE::CRUSH:
		Crush();
		break;
	case BOSSTYPE::SEARCH:
		Search();
		break;
	case BOSSTYPE::PULL:
		Pull();
		break;
	case BOSSTYPE::DOWN:
		Down();
		break;
	case BOSSTYPE::IDLE:
		Idle();
		break;
	}

	if (oldtype == type) {

	}
	else {

		switch (type) {
		case BOSSTYPE::RUSH:
			manager->animChange(8, &model, false, false, false);//突進前モーションをアタッチする
			manager->setNextAnim(9, &model, true, false);//突進モーションをアタッチする
			break;
		case BOSSTYPE::CAPTURE:
			manager->animChange(2, &model, false, false, false);//捕まえるモーションをアタッチする
			manager->setNextAnim(1, &model, true, false);//ループモーションをアタッチする
			break;
		case BOSSTYPE::CAPTUREEND:
			manager->animChange(0, &model, true, false, false);//離す前モーションをアタッチする
			break;
		case BOSSTYPE::ROTATION:
			manager->animChange(10, &model, true, false, false);//回転モーションをアタッチする
			break;
		case BOSSTYPE::WALK:
			manager->animChange(11, &model, true, false, false);//歩きモーションをアタッチする
			break;
		case BOSSTYPE::CRUSH:
			manager->animChange(5, &model, false, false, false);//刺さるモーションをアタッチする
			manager->setNextAnim(4, &model, true, false);//じたばたモーションをアタッチする
			break;
		case BOSSTYPE::SEARCH:
			manager->animChange(10, &model, true, false, false);//回転モーションをアタッチする
			break;
		case BOSSTYPE::PULL:
			manager->animChange(3, &model, true, false, false);//離れるモーションをアタッチする
			break;
		case BOSSTYPE::DOWN:
			manager->animChange(6, &model, false, false, true);//ダウンモーションをアタッチする
			break;
		case BOSSTYPE::IDLE:
			manager->animChange(7, &model, true, false, false);//待機モーションをアタッチする
		}
	}

	if (abs(swampDir.y * DX_PI_F / 180.0f) >= 360.f)
	{
		swampDir.y = 0.f;
	}

	swampDegreeDir.y = swampDir.y * DX_PI_F / 180.0f;

	for (int i = 0; i < swamps.size(); i++)
	{
		swamps[i]->Update(swamps);
	}
	for (int i = 0; i < swamps.size(); i++)
	{
		if (swamps[i]->neutralization)
		{
			swamps.erase(swamps.begin() + i);
		}
	}
	damage.SwampColl(swamps);
}

void Boss::Rotation(VECTOR sanPos, VECTOR lkaPos) {
	if (rotateFlag) {
		if (!BossSearchflag)
		{
			PlaySoundMem(BossSearch, DX_PLAYTYPE_BACK, true);
			BossSearchflag = true;
		}
		if (RotateCount <= 90) {
			BossDir = VNorm(VSub(sanPos, model.pos));
		}
		else if (RotateCount <= 180 && RotateCount > 90) {
			BossDir = VNorm(VSub(lkaPos, model.pos));
		}
		float dir{ 1.0f };
		float xz{ 65.8f };
		if (VCross(forward, BossDir).y < 0) {
			dir = -1.0f;
			xz = -65.8f;
		}
		model.dir.y += 0.02f * dir;
		swampDir.y += xz/* dir * 65.9f*/;
		//model.dir.y = fmod(model.dir.y, 2 * DX_PI);//一周したらdir.yを0に戻す
		//type = BOSSTYPE::ROTATION;
		RotateCount += 1;
		if (RotateCount > 180) {
			RotateCount = 0;
			rotateFlag = false;
			BossSearchflag = false;
			targetFlag = true;
			StopSoundMem(BossSearch);
		}
	}
	else {
		Targeting(san->vPos, lka->vPos);
	}
}

void Boss::Targeting(VECTOR sanPos, VECTOR lkaPos) {
	if (targetFlag) {
		float San = VSize(VSub(sanPos, model.pos));
		float Lka = VSize(VSub(lkaPos, model.pos));
		if (San <= Lka) {
			target = true;
		}
		else {
			target = false;
		}
		//BossDir.y = atan2(BossDir.z, BossDir.x);
		targetFlag = false;
	}
	if (target) {
		BossDir = VNorm(VSub(sanPos, model.pos));
	}
	else {
		BossDir = VNorm(VSub(lkaPos, model.pos));
	}
	float dir{ 1.0f };
	float xz{ 65.8f };
	if (VCross(forward, BossDir).y < 0) {
		dir = -1.0f;
		xz = -65.8f;
	}
	model.dir.y += 0.02f * dir;
	swampDir.y += xz /*dir * 65.9f*/;
	//model.dir.y = fmod(model.dir.y, 2 * DX_PI);//一周したらdir.yを0に戻す
	if (StopDir > VCross(forward, BossDir).y) {
		rushFlag = true;
		type = BOSSTYPE::RUSH;
	}
}

void Boss::Walk() {
	model.pos = VAdd(VScale(forward, 4.f), model.pos);
	//type = BOSSTYPE::WALK;
	if (StopPos > abs(BossSetDir.x - model.pos.x) && StopPos > abs(BossSetDir.z - model.pos.z)) {
		type = BOSSTYPE::IDLE;
	}

}

void Boss::Idle() {
	IdleCount += 1;
	if (IdleCount == 240) {
		type = BOSSTYPE::ROTATION;
		rotateFlag = true;
		IdleCount = 0;
	}
}

void Boss::Rush(VECTOR sanPos, VECTOR lkaPos, int SanHandle, int LkaHandle, int MapHandle) {
	MV1RefreshCollInfo(model.modelHandle, 2);
	MV1_COLL_RESULT_POLY_DIM hitPolyDimSan;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimLka;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimWall;
	if (rushFlag == true) {
		WaitCount += 1;
		if (WaitCount == 60) {
			WaitCount = 0;
			rushFlag = false;
		}
	}
	else {
		model.pos = VAdd(VScale(forward, 60.f), model.pos);
		MV1RefreshCollInfo(SanHandle, 3);
		MV1RefreshCollInfo(LkaHandle, 8);
		hitPolyDimSan = MV1CollCheck_Sphere(SanHandle, 3, SphereCenter, 50);
		hitPolyDimLka = MV1CollCheck_Sphere(LkaHandle, 8, SphereCenter, 50);
		hitPolyDimWall = MV1CollCheck_Sphere(MapHandle, 1, SphereCenter, 50);

		if (hitPolyDimSan.HitNum >= 1) {
			san->vPos.x = SphereCenter.x;
			san->vPos.y = 0;
			san->vPos.z = SphereCenter.z;
			SanCatchFlag = true;
		}
		else if (hitPolyDimLka.HitNum >= 1) {
			lka->vPos.x = SphereCenter.x;
			lka->vPos.y = 0;
			lka->vPos.z = SphereCenter.z;
			LkaCatchFlag = true;
		}
		if (hitPolyDimWall.HitNum >= 1) {
			crushFlag = true;
		}


	}
	if (SanCatchFlag || LkaCatchFlag) {
		type = BOSSTYPE::CAPTURE;
		crushFlag = false;
	}
	else if ((!SanCatchFlag && crushFlag) || (!LkaCatchFlag && crushFlag)) {
		type = BOSSTYPE::CRUSH;
		crushFlag = false;
	}

}

void Boss::Crush() {				//壁衝突時処理
	MV1RefreshCollInfo(model.modelHandle, 2);
	MV1_COLL_RESULT_POLY_DIM hitPolyDimSan;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimLka;
	hitPolyDimSan = MV1CollCheck_Sphere(model.modelHandle, 2, sanB->vPos, sanB->sphereMax);
	hitPolyDimLka = MV1CollCheck_Sphere(model.modelHandle, 2, lkaB->vPos, lkaB->sphereMax);

	if (sanB->situation == sanB->PlayerBomb::Throw && hitPolyDimSan.HitNum >= 1) {
		AttackedFlag = true;
		bosshitEf = true;
		switch (phType) {
		case PH::NONE:
			BossHP -= 10;
			break;
		case PH::ACID:
			BossHP -= 5;
			break;
		case PH::ALKALI:
			BossHP -= 20;
			break;
		}
	}
	if (lkaB->situation == lkaB->PlayerBomb::Throw && hitPolyDimLka.HitNum >= 1) {
		AttackedFlag = true;
		bosshitEf = true;
		switch (phType) {
		case PH::NONE:
			BossHP -= 10;
			break;
		case PH::ACID:
			BossHP -= 20;
			break;
		case PH::ALKALI:
			BossHP -= 5;
			break;
		}
	}
	if (phType == PH::ACID && CrushCount == 0)
	{
		SwampSpawn(true); SwampCnt--;
	}
	if (phType == PH::ALKALI && CrushCount == 0)
	{
		SwampSpawn(false); SwampCnt--;
	}
	if (SwampCnt == 0) {
		phType = PH::NONE;
		oldphType = PH::NONE;
	}
	CrushCount += 1;
	if (CrushCount >= 240 || AttackedFlag) {
		CrushCount = 0;
		AttackedFlag = false;
		type = BOSSTYPE::PULL;
	}
	if (BossHP <= 0) {
		type = BOSSTYPE::DOWN;
	}
}

void Boss::Search() {
	//int num;
	if (searchFlag) {
		int num = GetRand(3);
		searchFlag = false;
		switch (num) {
		case 0:
			BossDir = BossPosition0;
			BossSetDir = BossPosition0;
			break;
		case 1:
			BossDir = BossPosition1;
			BossSetDir = BossPosition1;
			break;
		case 2:
			BossDir = BossPosition2;
			BossSetDir = BossPosition2;
			break;
		case 3:
			BossDir = BossPosition3;
			BossSetDir = BossPosition3;
			break;
		}
		BossDir = VNorm(VSub(BossDir, model.pos));
	}

	float dir{ 1.0f };
	float xz{ 65.8f };
	if (VCross(forward, BossDir).y < 0) {
		dir = -1.0f;
		xz = -65.8f;
	}
	VECTOR Forward = VNorm(forward);
	model.dir.y += 0.02f * dir;
	swampDir.y += xz /*dir * 65.9f*/;
	if (StopDir > abs(1 - VDot(forward, BossDir))) {
		type = BOSSTYPE::WALK;
	}

}

void Boss::Pull() {
	PullCount += 1;
	if (PullCount > 60) {
		model.pos = VAdd(model.pos, VScale(forward, -3));

	}
	if (PullCount == 78) {
		PullCount = 0;
		searchFlag = true;
		type = BOSSTYPE::SEARCH;
	}
}

void Boss::Capture() {
	if (!BossSuckflag)
	{
		PlaySoundMem(BossSuck, DX_PLAYTYPE_BACK, true);
		BossSuckflag = true;
	}
	if (SanCatchFlag) {
		san->vPos.x = SphereCenter.x;
		san->vPos.y = 60;
		san->vPos.z = SphereCenter.z;
	}
	if (LkaCatchFlag) {
		lka->vPos.x = SphereCenter.x;
		lka->vPos.y = 60;
		lka->vPos.z = SphereCenter.z;
	}
	CaptureCount += 1;

	MV1_COLL_RESULT_POLY_DIM hitPolyDimSan;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimLka;
	hitPolyDimSan = MV1CollCheck_Sphere(model.modelHandle, 2, sanB->vPos, sanB->sphereMax);
	hitPolyDimLka = MV1CollCheck_Sphere(model.modelHandle, 2, lkaB->vPos, lkaB->sphereMax);

	if (sanB->situation == sanB->PlayerBomb::Throw && hitPolyDimSan.HitNum >= 1) {
		AttackedFlag = true;
		bosshitEf = true;
		switch (phType) {
		case PH::NONE:
			BossHP -= 10;
			break;
		case PH::ACID:
			BossHP -= 5;
			break;
		case PH::ALKALI:
			BossHP -= 20;
			break;
		}
		StopSoundMem(BossSuck);
	}
	if (lkaB->situation == lkaB->PlayerBomb::Throw && hitPolyDimLka.HitNum >= 1) {
		AttackedFlag = true;
		bosshitEf = true;
		switch (phType) {
		case PH::NONE:
			BossHP -= 10;
			break;
		case PH::ACID:
			BossHP -= 20;
			break;
		case PH::ALKALI:
			BossHP -= 5;
			break;
		}
		StopSoundMem(BossSuck);
	}

	if (CaptureCount == 120) {
		if (SanCatchFlag) {
			san->HP -= 1;
			sanhitEf = true;
			StartJoypadVibration(DX_INPUT_PAD1, 750, 300, -1);
			phType = PH::ACID;
			if (oldphType == PH::NONE) {
				oldphType = PH::ACID;
				SwampCnt = 3;
			}
			else if (oldphType == PH::ALKALI) {
				phType = PH::NONE;
				oldphType = PH::NONE;
				SwampCnt = 0;
			}
		}
		if (LkaCatchFlag) {
			lka->HP -= 1;
			lkahitEf = true;
			StartJoypadVibration(DX_INPUT_PAD2, 750, 300, -1);
			phType = PH::ALKALI;
			if (oldphType == PH::NONE) {
				oldphType = PH::ALKALI;
				SwampCnt = 3;
			}
			else if (oldphType == PH::ACID) {
				phType = PH::NONE;
				oldphType = PH::NONE;
				SwampCnt = 0;
			}
		}
	}
	if (CaptureCount == 180) {
		CaptureCount = 0;
		BossSuckflag = false;
		type = BOSSTYPE::CAPTUREEND;
	}
	if (AttackedFlag) {
		CaptureCount = 0;
		AttackedFlag = false;
		BossSuckflag = false;
		type = BOSSTYPE::CAPTUREEND;
	}
	if (BossHP <= 0) {
		type = BOSSTYPE::DOWN;
	}

}


void Boss::CaptureEnd() {
	EndCount += 1;
	if (EndCount > 45) {
		model.pos = VAdd(model.pos, VScale(forward, -3));
	}
	if (EndCount == 64) {
		EndCount = 0;
		SanCatchFlag = false;
		LkaCatchFlag = false;
		type = BOSSTYPE::IDLE;
	}
}

void Boss::Down() {
	DownCount += 1;
	if (DownCount == 459) {
		bossdownEf = true;
	}
}

void Boss::SwampSpawn(bool IsSan)
{
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;
	for (int z = 0; z < 3; z++)
	{
		for (int x = 0; x < 3; x++)
		{
			int a = -1;
			int b = 100;
			int c = -100;
			auto SwampPos = model.pos;

			if ((swampDegreeDir.y >= 45 && swampDegreeDir.y < 135) || (swampDegreeDir.y <= -225 && swampDegreeDir.y > -315))
			{
				SwampPos.x += (-50 + 100 * x); SwampPos.z += (100 - 100 * z);
			}

			if ((swampDegreeDir.y >= 135 && swampDegreeDir.y < 225) || ((swampDegreeDir.y <= -315 && swampDegreeDir.y > -360) || (swampDegreeDir.y <= 0 && swampDegreeDir.y > -45)))
			{
				SwampPos.x += (100 - 100 * x); SwampPos.z += (50 - 100 * z);
			}

			if ((swampDegreeDir.y >= 225 && swampDegreeDir.y < 315) || (swampDegreeDir.y <= -45 && swampDegreeDir.y > -135))
			{
				SwampPos.x += (50 - 100 * x); SwampPos.z += (100 - 100 * z);
			}

			if (((swampDegreeDir.y >= 315 && swampDegreeDir.y < 360) || (swampDegreeDir.y >= 0 && swampDegreeDir.y < 45)) || (swampDegreeDir.y <= -135 && swampDegreeDir.y > -225))
			{
				SwampPos.x += (-100 + 100 * x); SwampPos.z += (-50 + 100 * z);
			}

			SwampPos.y = 85.f;



			auto swamp = std::make_unique<BossSwamp>();
			swamp->Initialize(IsSan, SwampPos, handleBaseSan, handleBaseLka);
			swamp->CollCheck(swamps);
			swamps.emplace_back(std::move(swamp));
		}
	}
	top = false;
	bottom = false;
	left = false;
	right = false;
}

void Boss::Render()
{
	DrawGraph(300, 900, iconhandle, true);
	DrawGraph(300, 950, flamehandle, true);
	float HPgauge = (1185.0f / BossMaxHP) * BossHP;
	DrawRectGraph(310, 960, 0, 0, static_cast<int>(HPgauge), 30, HPhandle, true, false);

	{
		if (!downFlag) {
			if (type == BOSSTYPE::RUSH && WaitCount <= 60) {
				manager->modelRender(&model, 2.f, 1.f);
			}
			else {
				manager->modelRender(&model, 1.f, 1.f);
			}
		}

		switch (phType) {
		case PH::ACID:
			MV1SetTextureGraphHandle(model.modelHandle, 1, acidHandle, FALSE);
			MV1SetTextureGraphHandle(model.modelHandle, 2, acidHandle, FALSE);
			break;
		case PH::ALKALI:
			MV1SetTextureGraphHandle(model.modelHandle, 1, alkaliHandle, FALSE);
			MV1SetTextureGraphHandle(model.modelHandle, 2, alkaliHandle, FALSE);
			break;
		case PH::NONE:
			MV1SetTextureGraphHandle(model.modelHandle, 1, noneHandle, FALSE);
			MV1SetTextureGraphHandle(model.modelHandle, 2, noneHandle, FALSE);
			break;
		}
		for (int i = 0; i < swamps.size(); i++)
		{
			swamps[i]->Render();
		}
		//DrawFormatString(0, 200, GetColor(255, 0, 0), "BossHP = %d", BossHP);
		//DrawSphere3D(SphereCenter, 50, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
#ifdef debug
		DrawSphere3D(SphereCenter, 50, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);

		DrawFormatString(0, 0, GetColor(255, 0, 0), "BossDir.y = %f", BossDir.y);
		DrawFormatString(0, 50, GetColor(255, 0, 0), "model.dir.y = %f", model.dir.y);
		DrawFormatString(0, 100, GetColor(255, 0, 0), "HandPos = %f,%f,%f", HandPos.x, HandPos.y, HandPos.z);
		DrawFormatString(0, 150, GetColor(255, 0, 0), "SanCatchFlag = %d", SanCatchFlag);
		DrawFormatString(0, 200, GetColor(255, 0, 0), "BossHP = %d", BossHP);
		DrawFormatString(0, 250, GetColor(255, 0, 0), "BossDir.y = %f", BossDir.y);
#endif
		}
	}
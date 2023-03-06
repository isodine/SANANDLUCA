#include "SANclass.h"
#include "LKAclass.h"

void Boss::Initialize() {
	//BossHandle = MV1LoadModel("res/Boss/beaker_robot_All220203.mv1");
	model.pos = VGet(0, 0, 750);
	BossDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	model.dir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	StopDir = 0.05;
	TargetDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	rotate = 0;
	rotateFlag = true;
	walkFlag = false;
	walkTimeCount = 0;
	walkTime0 = 90;
	walkTime1 = 120;
	walkTime2 = 150;
	walkRand = 0;
	CrushCount = 0;
	PullCount = 0;
	WaitCount = 0;
	IdleCount = 0;
	/*rotateFlag = false;
	walkFlag = false;
	rushFlag = false;
	targetFlag = false;
	target = false;
	idleFlag = false;
	SanCatchFlag = false;
	LkaCatchFlag = false;
	crashFlag = false;*/
	
	type = BOSSTYPE::NONE;
	//モデルをメモリに読み込んでいる
	manager->modelImport("res/Boss/beaker_robot_All220217.mv1", 1.f, &model);
	//拡大率の適用
	manager->changeScale(&model);

}

void Boss::Terminate() {

}

void Boss::Process() {
	HandPos = MV1GetFramePosition(model.modelHandle, 3);
	AddPos = VNorm(VSub(MV1GetFramePosition(model.modelHandle, 5), HandPos));
	SphereCenter = VAdd(HandPos, VScale(AddPos, 90));
	BOSSTYPE oldtype = type;

	rotationMatrix = MMult(MMult(MGetRotX(model.dir.x), MGetRotY(model.dir.y)), MGetRotZ(model.dir.z));
	forward = VTransform({0.0f,0.0f,-1.0f},rotationMatrix);

	switch (type) {
	case BOSSTYPE::NONE:
		type = BOSSTYPE::ROTATION;
		break;
	case BOSSTYPE::RUSH:
		Rush(san->vPos, lka->vPos, san->vDir, lka->vDir, san->Mhandle, lka->Mhandle, modeboss->_handleMap);
		break;
	case BOSSTYPE::CAPTURE:
		
		break;
	case BOSSTYPE::CAPTUREEND:
		
		break;
	case BOSSTYPE::ROTATION:
		Rotation(san->vPos, lka->vPos, san->vDir, lka->vDir);
		break;
	case BOSSTYPE::WALK:
		Walk();
		break;
	case BOSSTYPE::CRUSH:
		Crush();
		break;
	case BOSSTYPE::PULL:
		Pull();
		break;
	case BOSSTYPE::DOWN:
		
		break;
	case BOSSTYPE::IDLE:
		Idle();
		break;
	}




	/*Rotation(san.vPos, lka.vPos, san.vDir, lka.vDir);
	Walk();
	Rush(san.vPos, lka.vPos, san.vDir, lka.vDir);*/
	if (oldtype == type) {
		// 再生時間を進める
		PlayTime += 0.5f;
		if (PlayTime >= TotalTime1)
		{
			PlayTime = 0.0f;
		}
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (AttachAnim1 != -1) {
			MV1DetachAnim(BossHandle, AttachAnim1);
			AttachAnim1 = -1;
		}
	
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
	case BOSSTYPE::PULL:
		manager->animChange(3, &model, true, false, false);//離れるモーションをアタッチする
		break;
	case BOSSTYPE::DOWN:
		//AttachAnim1 = MV1AttachAnim(BossHandle, 6, -1, FALSE);//ダウンモーションをアタッチする
		manager->animChange(6, &model, false, false, true);
		break;
	case BOSSTYPE::IDLE:
		manager->animChange(7, &model, true, false, false);//待機モーションをアタッチする
	}
}
	/*TotalTime1 = MV1GetAttachAnimTotalTime(BossHandle, AttachAnim1);
	MV1SetAttachAnimTime(BossHandle, AttachAnim1, PlayTime);*/
	// 再生時間を初期化
	//PlayTime = 0.0f;	
}

void Boss::Rotation(VECTOR sanPos, VECTOR lkaPos, VECTOR sanDir, VECTOR lkaDir) {
	if (rotateFlag) {
		if (RotateCount <= 90) {
			BossDir = VNorm(VSub(sanPos, model.pos));
		}
		else if (RotateCount <= 180 && RotateCount > 90) {
			BossDir = VNorm(VSub(lkaPos, model.pos));
		}
		float dir{ 1.0f };
		if (VCross(forward, BossDir).y < 0) {
			dir = -1.0f;
		}
		model.dir.y += 0.02f * dir;
		//model.dir.y = fmod(model.dir.y, 2 * DX_PI);//一周したらdir.yを0に戻す
		type = BOSSTYPE::ROTATION;
		RotateCount += 1;
		if (RotateCount > 180) {
			RotateCount = 0;
			rotateFlag = false;
			targetFlag = true;
		}
	}
	else {
		Targeting(san->vPos, lka->vPos, san->vDir, lka->vDir);
	}
}

void Boss::Targeting(VECTOR sanPos, VECTOR lkaPos, VECTOR sanDir, VECTOR lkaDir) {
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
	if (VCross(forward, BossDir).y < 0) {
		dir = -1.0f;
	}
	model.dir.y += 0.02f * dir;
	//model.dir.y = fmod(model.dir.y, 2 * DX_PI);//一周したらdir.yを0に戻す
	if (StopDir > VCross(forward, BossDir).y) {
		rushFlag = true;
		type = BOSSTYPE::RUSH;
	}
}

void Boss::Walk() {
	if (walkFlag) {
		type = BOSSTYPE::WALK;
		model.pos = VAdd(VScale(forward, 2.f), model.pos);
		walkTimeCount += 1;
		if (walkTimeCount == WalkTime) {
			int num = GetRand(3);
			if (num == 0) {
				rotateFlag = true;
				rushFlag = true;
				targetFlag = true;
				rushFlag = true;
			}
			walkFlag = false;
			rotateFlag = true;
		}
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

void Boss::Rush(VECTOR sanPos, VECTOR lkaPos, VECTOR sanDir, VECTOR lkaDir, int SanHandle, int LkaHandle, int MapHandle) {
	MV1_COLL_RESULT_POLY_DIM hitPolyDimSan;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimLka;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimWall;
	if (rushFlag == true) {
		WaitCount += 1;
		if (WaitCount == 120) {
			WaitCount = 0;
			rushFlag = false;
		}
	}
	else {
		model.pos = VAdd(VScale(forward, 10.f), model.pos);
		MV1RefreshCollInfo(SanHandle, 3);
		MV1RefreshCollInfo(LkaHandle, 3);
		hitPolyDimSan = MV1CollCheck_Sphere(SanHandle, 3, SphereCenter, 60);
		hitPolyDimLka = MV1CollCheck_Sphere(LkaHandle, 3, SphereCenter, 60);
		hitPolyDimWall = MV1CollCheck_Sphere(MapHandle, 1, SphereCenter, 60);

		if (hitPolyDimSan.HitNum >= 1) {
			san->vPos = SphereCenter;
			SanCatchFlag = true;
		}
		else if (hitPolyDimLka.HitNum >= 1) {
			lka->vPos = SphereCenter;
			LkaCatchFlag = true;
		}
		if (hitPolyDimWall.HitNum >= 1) {
			crushFlag = true;
		}

		
	}
	if ((SanCatchFlag && crushFlag) || (LkaCatchFlag && crushFlag)) {
		type = BOSSTYPE::CAPTURE;
		crushFlag = false;
	}
	else if ((!SanCatchFlag && crushFlag) || (!LkaCatchFlag && crushFlag)) {
		type = BOSSTYPE::CRUSH;
		crushFlag = false;
	}

}

void Boss::Crush() {
	CrushCount += 1;
	if (CrushCount >= 240) {
		CrushCount = 0;
		type = BOSSTYPE::PULL;
	}
}

void Boss::Pull() {
	PullCount += 1;
	if (PullCount == 60) {
		model.pos = VAdd(model.pos, VScale(forward, -10));
	}
	if (PullCount == 78) {
		PullCount = 0;
		type = BOSSTYPE::IDLE;
	}
}

void Boss::Render() {
	{
		/*MV1SetRotationXYZ(BossHandle, BossSetDir);
		MV1SetPosition(BossHandle, model.pos);
		MV1DrawModel(BossHandle);*/
		manager->modelRender(&model, 1.f, 1.f);
		DrawSphere3D(SphereCenter, 60, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);

		DrawFormatString(0, 0, GetColor(255, 0, 0), "BossDir.y = %f", BossDir.y);
		DrawFormatString(0, 50, GetColor(255, 0, 0), "model.dir.y = %f", model.dir.y);
		DrawFormatString(0, 100, GetColor(255, 0, 0), "HandPos = %f,%f,%f", HandPos.x, HandPos.y, HandPos.z);
		DrawFormatString(0, 150, GetColor(255, 0, 0), "WalkTime = %d", WalkTime);
	}
}
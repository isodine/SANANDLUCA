//#include "Boss.h"

void Boss::Initialize() {
	//BossHandle = MV1LoadModel("res/Boss/beaker_robot_All220203.mv1");
	model.pos = VGet(0, 0, 750);
	BossDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	model.dir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	StopDir = 0.01;
	TargetDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	rotate = 0;
	rotateFlag = true;
	walkFlag = false;
	walkTimeCount = 0;
	walkTime0 = 90;
	walkTime1 = 120;
	walkTime2 = 150;
	walkRand = 0;
	rushFlag = false;
	targetFlag = false;
	type = BOSSTYPE::NONE;
	//モデルをメモリに読み込んでいる
	manager->modelImport("res/Boss/beaker_robot_All220203.mv1", 1.f, &model);
	//拡大率の適用
	manager->changeScale(&model);

}

void Boss::Terminate() {

}

void Boss::Process() {
	HandPos = MV1GetFramePosition(model.modelHandle, 3);
	AddPos = VNorm(VSub(HandPos, MV1GetFramePosition(model.modelHandle, 1)));
	BOSSTYPE oldtype = type;

	rotationMatrix = MMult(MMult(MGetRotX(model.dir.x), MGetRotY(model.dir.y)), MGetRotZ(model.dir.z));
	forward = VTransform({0.0f,0.0f,-1.0f},rotationMatrix);

	Rotation(san.vPos, lka.vPos, san.vDir, lka.vDir);
	Walk();
	Rush(san.vPos, lka.vPos, san.vDir, lka.vDir);
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
	
	if (rotateCount <= 90) {
		//model.dir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		BossDir = VNorm(VSub(sanDir, model.dir));
		//model.dir.y = model.dir.y,VScale(BossDir,0.01);
	}
	else if (rotateCount >= 180 && rotateCount > 90) {
		//model.dir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		BossDir = VNorm(VSub(lkaDir, model.dir));
		//model.dir.y = model.dir.y + BossDir.y * 0.01;
	}
	model.dir.y = model.dir.y + BossDir.y * 0.01;
	//model.dir.y = std::fmod(model.dir.y, 2 * DX_PI_F);
	type = BOSSTYPE::ROTATION;
	rotateCount += 1;
	if (rotateCount > 180) {
		rotateCount = 0;
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

}

void Boss::Rush(VECTOR sanPos, VECTOR lkaPos, VECTOR sanDir, VECTOR lkaDir) {
	if (rushFlag == true) {
		//一度だけターゲットを決める
		if (targetFlag == true) {
			VECTOR LkaPos = VSub(lkaPos, model.pos);
			VECTOR SanPos = VSub(sanPos, model.pos);

			float SanDir = VSize(SanPos);
			float LkaDir = VSize(LkaPos);
			targetFlag = false;
			if (SanDir <= LkaDir) {
				target = true;
				BossDir = SanPos;
			}
			else {
				target = false;
				BossDir.y = LkaPos.y;
			}
		}
		if (StopDir > abs(model.dir.y - BossDir.y)) {
			rotate = 0.15;
			if (target) {
				//model.dir.y = atan2(sanPos.x * -1, sanPos.z * -1);
				model.dir = VAdd(model.dir, VGet(0, rotate, 0));
				model.dir.y = std::fmod(model.dir.y, 2 * DX_PI_F);
			}
			else {
				//model.dir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
				model.dir = VAdd(model.dir, VGet(0, rotate, 0));
				model.dir.y = std::fmod(model.dir.y, 2 * DX_PI_F);
			}
			TargetDir = VNorm(VGet(BossDir.x, model.dir.y * DX_PI_F / 180.0f, BossDir.z));
		}
		else {
			model.pos = VAdd(VScale(forward, 5.f), TargetDir);
		}
		

	}
	

}

void Boss::Render() {
	{
		/*MV1SetRotationXYZ(BossHandle, BossSetDir);
		MV1SetPosition(BossHandle, model.pos);
		MV1DrawModel(BossHandle);*/
		manager->modelRender(&model, 1.f, 1.f);
		DrawSphere3D(VAdd(HandPos, VScale(AddPos,50)), 40, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);

		DrawFormatString(0, 0, GetColor(255, 0, 0), "BossDir = %f", BossDir.y);
		DrawFormatString(0, 50, GetColor(255, 0, 0), "BossSetDir = %f", model.dir.y);
		DrawFormatString(0, 100, GetColor(255, 0, 0), "HandPos = %f,%f,%f", HandPos.x, HandPos.y, HandPos.z);
		DrawFormatString(0, 150, GetColor(255, 0, 0), "WalkTime = %d", WalkTime);
	}
}
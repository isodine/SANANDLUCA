//#include "Boss.h"

void Boss::Initialize() {
	//BossHandle = MV1LoadModel("res/Boss/beaker_robot_All220203.mv1");
	model.pos = VGet(0, 0, 750);
	BossDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	model.dir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	StopDir = 0.1;
	rotateFlag = true;
	walkFlag = false;
	walkTimeCount = 0;
	walkTime0 = 180;
	walkTime1 = 210;
	walkTime2 = 240;
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

	Rotation();
	Walk();
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
		AttachAnim1 = MV1AttachAnim(BossHandle, 8, -1, FALSE);//突進前モーションをアタッチする
		AttachAnim2 = MV1AttachAnim(BossHandle, 9, -1, FALSE);//突進モーションをアタッチする
		break;
	case BOSSTYPE::CAPTURE:
		AttachAnim1 = MV1AttachAnim(BossHandle, 2, -1, FALSE);//捕まえるモーションをアタッチする
		AttachAnim2 = MV1AttachAnim(BossHandle, 1, -1, FALSE);//ループモーションをアタッチする
		AttachAnim3 = MV1AttachAnim(BossHandle, 0, -1, FALSE);//離す前モーションをアタッチする
		break;
	case BOSSTYPE::ROTATION:
		manager->animChange(10, &model, true, false, false);//回転モーションをアタッチする
		break;
	case BOSSTYPE::WALK:
		manager->animChange(11, &model, true, false, false);//歩きモーションをアタッチする
		break;
	case BOSSTYPE::CRUSH:
		AttachAnim1 = MV1AttachAnim(BossHandle, 5, -1, FALSE);//刺さるモーションをアタッチする
		AttachAnim2 = MV1AttachAnim(BossHandle, 4, -1, FALSE);//じたばたモーションをアタッチする
		AttachAnim3 = MV1AttachAnim(BossHandle, 3, -1, FALSE);//離れるモーションをアタッチする
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

void Boss::Rotation() {
	float rotate;
	if (rotateFlag) {
		randomNum = GetRand(359);
		BossDir = VGet(0, randomNum * DX_PI_F / 180.0f, 0);
		walkRand = GetRand(2);
		if (walkRand == 0) {
			WalkTime = walkTime0;
		}
		else if (walkRand == 1) {
			WalkTime = walkTime1;
		}
		else if (walkRand == 2) {
			WalkTime = walkTime2;
		}
		walkTimeCount = 0;
		rotateFlag = false;
	}
	if (StopDir < abs(model.dir.y-BossDir.y)) {
		if (model.dir.y - BossDir.y > 0) {
			rotate = -0.015;
		}
		else {
			rotate = 0.015;
		}
		model.dir = VAdd(model.dir, VGet(0, rotate, 0));
		model.dir.y = std::fmod(model.dir.y, 2 * DX_PI_F);
		type = BOSSTYPE::ROTATION;
	}
	else {
		walkFlag = true;
	}
}

void Boss::Walk() {
	if (walkFlag) {
		type = BOSSTYPE::WALK;
		model.pos = VAdd(VScale(forward, 2.f), model.pos);
		walkTimeCount += 1;
		if (walkTimeCount == WalkTime) {
			int num = GetRand(9);
			if (num == 0) {
				rotateFlag = true;
				rushFlag = true;
				targetFlag = true;
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
			}
			else {
				target = false;
			}
		}
		if (target == true) {
			BossSetDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		}
		else {
			BossSetDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
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
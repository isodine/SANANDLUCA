//#include "Boss.h"

void Boss::Initialize() {
	BossHandle = MV1LoadModel("res/Boss/beaker_robot_All220203.mv1");
	BossPos = VGet(1000, 500, 0);
	BossDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	BossOldDir = VGet(0, 0 * DX_PI_F / 180.0f, 0);
	BossSetDir = VGet(0, 90 * DX_PI_F / 180.0f, 0);
	rotateFlag = true;
	type = BOSSTYPE::NONE;
}

void Boss::Terminate() {

}

void Boss::Process() {
	HandPos = MV1GetFramePosition(BossHandle, 3);
	Rotation();

	BOSSTYPE oldtype = type;

	if (oldtype == type) {
		// 再生時間を進める
		PlayTime += 0.5f;
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (AttachAnim1 != -1 || AttachAnim2 != -1 || AttachAnim3 != -1) {
			MV1DetachAnim(BossHandle, AttachAnim1);
			MV1DetachAnim(BossHandle, AttachAnim2);
			MV1DetachAnim(BossHandle, AttachAnim3);
			AttachAnim1 = -1;
			AttachAnim2 = -1;
			AttachAnim3 = -1;
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
		AttachAnim1 = MV1AttachAnim(BossHandle, 10, -1, FALSE);//回転モーションをアタッチする
		break;
	case BOSSTYPE::WALK:
		AttachAnim1 = MV1AttachAnim(BossHandle, 11, -1, FALSE);//歩きモーションをアタッチする
		break;
	case BOSSTYPE::CRUSH:
		AttachAnim1 = MV1AttachAnim(BossHandle, 5, -1, FALSE);//刺さるモーションをアタッチする
		AttachAnim2 = MV1AttachAnim(BossHandle, 4, -1, FALSE);//じたばたモーションをアタッチする
		AttachAnim3 = MV1AttachAnim(BossHandle, 3, -1, FALSE);//離れるモーションをアタッチする
		break;
	case BOSSTYPE::DOWN:
		AttachAnim1 = MV1AttachAnim(BossHandle, 6, -1, FALSE);//ダウンモーションをアタッチする
		break;
	}

	TotalTime1 = MV1GetAttachAnimTotalTime(BossHandle, AttachAnim1);
	TotalTime2 = MV1GetAttachAnimTotalTime(BossHandle, AttachAnim2);
	TotalTime3 = MV1GetAttachAnimTotalTime(BossHandle, AttachAnim3);
	// 再生時間を初期化
	PlayTime = 0.0f;
}
	if (PlayTime >= TotalTime1 || PlayTime >= TotalTime2 || PlayTime >= TotalTime3)
	{
		PlayTime = 0.0f;
	}
}

void Boss::Rotation() {
	if (rotateFlag) {
		randomNum = GetRand(359);
		BossDir = VGet(0, randomNum * DX_PI_F / 180.0f, 0);
		BossOldDir = BossDir;
		rotateFlag = false;
	}
	if ((int)BossDir.y != (int)BossSetDir.y) {
		BossSetDir = VAdd(BossSetDir, VScale(BossDir, 0.002));
		type = BOSSTYPE::ROTATION;
	}
}

void Boss::Walk() {
	
}

void Boss::Render() {
	{
		MV1SetRotationXYZ(BossHandle, BossSetDir);
		MV1SetPosition(BossHandle, BossPos);
		MV1DrawModel(BossHandle);
		DrawSphere3D(VSub(BossPos, HandPos), 50, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
	}
}
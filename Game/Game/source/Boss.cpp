//#include "Boss.h"

void Boss::Initialize() {
	BossHandle = MV1LoadModel("res/Boss/beaker_robot_All220203.mv1");
	BossPos = VGet(1000, 500, 0);
}

void Boss::Terminate() {

}

void Boss::Process() {
	HandPos = MV1GetFramePosition(BossHandle, 3);
}

void Boss::Walk() {
	
}

void Boss::Render() {
	{
		//MV1SetRotationXYZ(BossHandle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
		MV1SetPosition(BossHandle, BossPos);
		MV1DrawModel(BossHandle);
		//DrawSphere3D(VSub(BossPos, HandPos), 50, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
	}
}
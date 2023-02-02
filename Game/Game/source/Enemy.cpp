#include "Enemy.h"


void Enemy::Initialize() {
	PlayTime = 0.0f;
	slimePos = VGet(-60, 25, 400);
	slimeDir = VGet(0, 0, 0);
	_status = STATUS::NONE;
	AttachAnim = -1;
	height = 5.0;
	slimecount = 0;
	slimeAttackFlag = false;
	slimeSerch = false;
}

void Enemy::Terminate() {

}

void Enemy::Process() {
	
}

void Enemy::Render() {

}

void Enemy::Slime(VECTOR SanPos, VECTOR LkaPos, int Handle, int HandleMap, float speed) {

	_rotationMatrix = MMult(MMult(MGetRotX(slimeDir.x), MGetRotY(slimeDir.y)), MGetRotZ(slimeDir.z));

	VECTOR forward{ VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };

	STATUS oldStatus = _status;
	VECTOR oldPos = slimePos;

	sanDistance = VSize(VSub(SanPos, slimePos));
	lkaDistance = VSize(VSub(LkaPos, slimePos));

	sanPos = VNorm(VSub(SanPos, slimePos));
	lkaPos = VNorm(VSub(LkaPos, slimePos));

	if (sanDistance < 130)
	{
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::ATTACK;
		slimeAttackFlag = true;

	}
	else if (lkaDistance < 130)
	{
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::ATTACK;
		slimeAttackFlag = true;
		
	}

	else if (sanDistance < lkaDistance && !slimeAttackFlag)
	{          //サンの方が近いときサンを追いかける
		slimeSerch = true;
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::WALK_KAI;
		
		slimePos = VAdd(slimePos, VScale(forward, speed));
	}
	else if (sanDistance >= lkaDistance && !slimeAttackFlag)
	{
		slimeSerch = false;
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::WALK_KAI;

		slimePos = VAdd(slimePos, VScale(forward, speed));
	}
	SlimeJump();


	// モーションが切り替わったか？
	if (oldStatus == _status) {
		PlayTime += 1.0f;
		if (PlayTime >= TotalTime)
		{
			PlayTime = 0.0f;
		}
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (AttachAnim != -1) {
			MV1DetachAnim(Handle, AttachAnim);
			AttachAnim = -1;
		}
		// ステータスに合わせてアニメーションをアタッチする
		switch (_status) {
		case STATUS::WALK_KAI:
			AttachAnim = MV1AttachAnim(Handle, 2, -1, FALSE);//歩きモーションをアタッチする
			break;
		case STATUS::ATTACK:
			AttachAnim = MV1AttachAnim(Handle, 0, -1, FALSE);//攻撃モーションをアタッチする
			break;
		case STATUS::HIT:
			AttachAnim = MV1AttachAnim(Handle, 1, -1, FALSE);//ダメージモーションをアタッチする
			break;
		}
		TotalTime = MV1GetAttachAnimTotalTime(Handle, AttachAnim);
		PlayTime = 0.0f;
	}

	MV1SetAttachAnimTime(Handle, AttachAnim, PlayTime);
}

void Enemy::Spider(VECTOR SanPos, VECTOR LkaPos, VECTOR SpiderPos, int Handle, float speed) {

}

void Enemy::Boss(VECTOR SanPos, VECTOR LkaPos, VECTOR BossPos, int Handle, float speed) {

}

void Enemy::SlimeJump() {
	if (!slimeAttackFlag) {
		return;
	}

	VECTOR forward{ VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	VECTOR up{ 0.0f,0.1f,0.0f };
	float spd = 2.0f;

	forward = VScale(forward, spd);
	slimecount += 1;
	if (slimeSerch == true) {
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
	}
	else {
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
	}
	if (slimecount <= 50 && slimecount != 0 && slimeAttackFlag == true) {
		slimePos = VAdd(slimePos, forward);
		slimePos = VAdd(slimePos, VScale(up, 2.0f));
	}
	else if (slimecount > 50 && slimecount != 60 && slimeAttackFlag == true) {
		slimePos = VSub(slimePos, VScale(forward,7.0f));
		slimePos = VSub(slimePos, VScale(up,11.0f));
	}
	else if (slimecount == 60) {
		slimecount = 0;
		slimeAttackFlag = false;
	}
}

void Enemy::SlimeRender(VECTOR Pos, int Handle) {
	MV1SetPosition(Handle, Pos);
	MV1SetScale(Handle, VGet(3.0f, 3.0f, 3.0f));
	MV1SetRotationXYZ(Handle, slimeDir);
	MV1DrawModel(Handle);
}

void Enemy::SpiderRender(VECTOR Pos, int Handle) {
	MV1SetPosition(Handle, Pos);
	MV1DrawModel(Handle);
}

void Enemy::BossRender(VECTOR Pos, int Handle) {
	MV1SetPosition(Handle, Pos);
	MV1DrawModel(Handle);
}
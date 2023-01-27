#include "Enemy.h"


void Enemy::Initialize(){
	PlayTime = 0.0f;
	slimePos = VGet(-60, 25, 400);
	slimeDir = VGet(0, 0, 0);
	_status = STATUS::NONE;
	AttachAnim = -1;
}

void Enemy::Terminate(){

}

void Enemy::Process() {

}

void Enemy::Render() {

}

void Enemy::Slime(VECTOR SanPos, VECTOR LkaPos, int Handle, float speed) {
	STATUS oldStatus = _status;
	
	sanDistance = VSize(VSub(SanPos, slimePos));
	lkaDistance = VSize(VSub(LkaPos, slimePos));

	

	sanPos = VNorm(VSub(SanPos, slimePos));
	lkaPos = VNorm(VSub(LkaPos, slimePos));

	if (sanDistance < 75)
	{                  
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
	_status = STATUS::ATTACK;
	}
	else if (lkaDistance < 75)
	{
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
	_status = STATUS::ATTACK;
	}

	else if (sanDistance < lkaDistance) 
	{          //サンの方が近いときサンを追いかける
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos.x += sanPos.x * speed;
		slimePos.z += sanPos.z * speed;
	}
	else if(sanDistance >= lkaDistance) 
	{
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos.x += lkaPos.x * speed;
		slimePos.z += lkaPos.z * speed;
	}
	
	

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

void Enemy::SlimeRender(VECTOR Pos, int Handle) {
	MV1SetPosition(Handle, Pos);
	MV1SetScale(Handle, VGet(3.0f,3.0f,3.0f));
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
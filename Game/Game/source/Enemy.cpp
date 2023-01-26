#include "Enemy.h"


void Enemy::Initialize(){
	PlayTime = 0.0f;
	slimePos = VGet(-60, 25, 400);
}

void Enemy::Terminate(){

}

void Enemy::Process() {

}

void Enemy::Render() {

}

void Enemy::Slime(VECTOR SanPos, VECTOR LkaPos, int Handle, int MapHandle, float speed) {
	
	sanDistance = VSize(VSub(SanPos, slimePos));
	lkaDistance = VSize(VSub(LkaPos, slimePos));

	sanPos = VNorm(VSub(SanPos, slimePos));
	lkaPos = VNorm(VSub(LkaPos, slimePos));

	if (sanDistance < lkaDistance) {          //サンの方が近いときサンを追いかける
		AttachAnim = MV1AttachAnim(Handle, 1, -1, TRUE);//歩きモーションをアタッチする
		TotalTime = MV1GetAttachAnimTotalTime(Handle, AttachAnim);
		PlayTime += 100.0f;
		if (PlayTime >= TotalTime)
		{
			PlayTime = 0.0f;
		}


		slimePos.x += sanPos.x * speed;
		slimePos.z += sanPos.z * speed;
	}
	else {
		AttachAnim = MV1AttachAnim(Handle, 2, -1, FALSE);//歩きモーションをアタッチする
		TotalTime = MV1GetAttachAnimTotalTime(Handle, AttachAnim);
		PlayTime += 100.0f;
		if (PlayTime >= TotalTime)
		{
			PlayTime = 0.0f;
		}


		slimePos.x += lkaPos.x * speed;
		slimePos.z += lkaPos.z * speed;
	}
	
	if (sanDistance < 50) {                   //ここで攻撃
		AttachAnim = MV1AttachAnim(Handle, 0, -1, FALSE);//攻撃モーションをアタッチする
		TotalTime = MV1GetAttachAnimTotalTime(Handle, AttachAnim);
		PlayTime += 1.0f;
		if (PlayTime >= TotalTime)
		{
			PlayTime = 0.0f;
		}

	}

	if (lkaDistance < 50) {
		AttachAnim = MV1AttachAnim(Handle, 0, -1, FALSE);//攻撃モーションをアタッチする
		TotalTime = MV1GetAttachAnimTotalTime(Handle, AttachAnim);
		PlayTime += 10.0f;
		if (PlayTime >= TotalTime)
		{
			PlayTime = 0.0f;
		}

	}
}

void Enemy::Spider(VECTOR SanPos, VECTOR LkaPos, VECTOR SpiderPos, int Handle, float speed) {

}

void Enemy::Boss(VECTOR SanPos, VECTOR LkaPos, VECTOR BossPos, int Handle, float speed) {

}

void Enemy::SlimeRender(VECTOR Pos, int Handle) {
	MV1SetPosition(Handle, Pos);
	//MV1SetScale(Handle, VGet(3.0f,3.0f,3.0f));
	MV1DrawModel(Handle);
	//DrawFormatString(0,200,GetColor(0,0,0),"s")
}

void Enemy::SpiderRender(VECTOR Pos, int Handle) {
	MV1SetPosition(Handle, Pos);
	MV1DrawModel(Handle);
}

void Enemy::BossRender(VECTOR Pos, int Handle) {
	MV1SetPosition(Handle, Pos);
	MV1DrawModel(Handle);
}
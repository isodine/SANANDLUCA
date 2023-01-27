#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeStage0.h"
#include "ModeStage1.h"
#include "ModeGameOver.h"

bool ModeStage0::Initialize() {
	if (!base::Initialize()) { return false; }
	handle= MV1LoadModel("res/Balance/Motion/Balance_MOmarge.mv1");
	Mattach_index = MV1AttachAnim(handle, 0, -1, FALSE);
	// アタッチしたアニメーションの総再生時間を取得する
	Mtotal_time = MV1GetAttachAnimTotalTime(handle, Mattach_index);
	// 再生時間を初期化
	Mplay_time = 0.0f;
	return true;
}

bool ModeStage0::Terminate() {
	base::Terminate();

	return true;
}

bool ModeStage0::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage1(), 1, "stage1");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "GameOver");
	}


		// 再生時間を進める
		Mplay_time += 0.5f;

		if(CheckHitKey(KEY_INPUT_S))
		{
			// アニメーションがアタッチされていたら、デタッチする
			if (Mattach_index != -1) {
				MV1DetachAnim(handle, Mattach_index);
				Mattach_index = -1;
			}
			Mattach_index = MV1AttachAnim(handle, 1, -1, FALSE);
		}

		
		// アタッチしたアニメーションの総再生時間を取得する
		Mtotal_time = MV1GetAttachAnimTotalTime(handle, Mattach_index);


	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (Mplay_time >= Mtotal_time) {
		Mplay_time = 0.0f;
	}

	return true;
}

bool ModeStage0::Render() {

	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	//DrawString(0, 0, "チュートリアルステージ", GetColor(255, 255, 255));
	MV1SetAttachAnimTime(handle, Mattach_index, Mplay_time);
	MV1SetPosition(handle, VGet(500.0f, 500.0f, 0.0f));
	//MV1SetScale(handle, VGet(3.0f, 3.0f, 3.0f));
	MV1DrawModel(handle);

	return true;
}
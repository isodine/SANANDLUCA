#include"LKAclass.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include <string>
#include <memory>
#include <vector>

LKA::LKA()
{
}

LKA::~LKA()
{
}

void LKA::Initialize()
{

}

void LKA::Update() {
	int key = ApplicationMain::GetInstance()->GetKey1P();
	int trg = ApplicationMain::GetInstance()->GetTrg1P();

	// 処理前のステータスを保存しておく
	STATUS oldStatus = _status;
	// カメラの向いている角度を取得
	float sx = _cam._vPos.x - _cam._vTarget.x;
	float sz = _cam._vPos.z - _cam._vTarget.z;
	float camrad = atan2(sz, sx);

	// 移動方向を決める
	VECTOR v = { 0,0,0 };
	float mvSpeed = 6.f;
	if (key & PAD_INPUT_5) { v.x = 1; }
	if (key & PAD_INPUT_8) { v.x = -1; }
	if (key & PAD_INPUT_4) { v.z = -1; }
	if (key & PAD_INPUT_6) { v.z = 1; }

	//if (key & PAD_INPUT_DOWN) { v.x = 1; }
	//if (key & PAD_INPUT_UP) { v.x = -1; }
	//if (key & PAD_INPUT_LEFT) { v.z = -1; }
	//if (key & PAD_INPUT_RIGHT) { v.z = 1; }
	if (key & PAD_INPUT_10 && !(_status == STATUS::JUMP)) { _status = STATUS::JUMP; }

	if (_status == STATUS::JUMP) { charJump(); }
	// vをrad分回転させる
	float length = 0.f;
	if (VSize(v) > 0.f) { length = mvSpeed; }
	float rad = atan2(v.z, v.x);
	v.x = cos(rad + camrad) * length;
	v.z = sin(rad + camrad) * length;

	// 移動前の位置を保存
	VECTOR oldvPos = vPos;

	// vの分移動
	vPos = VAdd(vPos, v);

	// 移動した先でコリジョン判定
	MV1_COLL_RESULT_POLY hitPoly;
	// 主人公の腰位置から下方向への直線
	hitPoly = MV1CollCheck_Line(_handleMap, ModeGame::_frameMapCollision,
		VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		// 当たった
		if (vPos.y < hitPoly.HitPosition.y) {
			throughtime = 0.0f;
			height = 0.0f;
			vPos.y = 0.f;
			_status = STATUS::WAIT;
		}
		// 当たったY位置をキャラ座標にする
		vPos.y = hitPoly.HitPosition.y + height;

		// カメラも移動する
		_cam._vPos = VAdd(_cam._vPos, v);
		_cam._vTarget = VAdd(_cam._vTarget, v);
	}
	else {
		// 当たらなかった。元の座標に戻す
		vPos = oldvPos;
	}

	// 移動量をそのままキャラの向きにする
	if (VSize(v) > 0.f) {		// 移動していない時は無視するため
		vDir = v;
		if (!(_status == STATUS::JUMP)) {
			_status = STATUS::WALK;
		}
	}
	else if (throughtime > 0.0f) {}
	else {
		_status = STATUS::WAIT;
	}


	// デバッグ機能
	//if (trg & PAD_INPUT_2) {
	//	_bViewCollision = !_bViewCollision;
	//}
	//if (_bViewCollision) {
	//	MV1SetFrameVisible(_handleMap, _frameMapCollision, TRUE);
	//}
	//else {
	//	MV1SetFrameVisible(_handleMap, _frameMapCollision, FALSE);
	//}

	// ステータスが変わっていないか？
	if (oldStatus == _status) {
		// 再生時間を進める
		_play_time += 0.5f;
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (_attach_index != -1) {
			MV1DetachAnim(_handle, _attach_index);
			_attach_index = -1;
		}
		// ステータスに合わせてアニメーションのアタッチ
		switch (_status) {
		case STATUS::WAIT:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "Anim003"), -1, FALSE);
			break;
		case STATUS::WALK:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "Anim004"), -1, FALSE);
			break;
		case STATUS::JUMP:
			_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handle, "Anim002"), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		Mtotal_time = MV1GetAttachAnimTotalTime(_handle, _attach_index);
		// 再生時間を初期化
		Mplay_time = 0.0f;
	}

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (_play_time >= _total_time) {
		_play_time = 0.0f;
	}
}

void LKA::Render() {}
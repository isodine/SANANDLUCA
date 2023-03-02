#include"SANclass.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

SAN::SAN()
	:Player()
{
}

SAN::~SAN()
{
}

void SAN::Initialize()
{
	// モデルデータのロード（テクスチャも読み込まれる)
	Mhandle = MV1LoadModel("res/Sun/モデル（テクスチャ込み）/sun multimotion2.mv1");
	hphandle[0] = LoadGraph("res/UI_san_v6.png");
	hphandle[1] = LoadGraph("res/UI_san_v5.png");
	Mattach_index = -1;		// アニメーションアタッチはされていない
	// ステータスを「無し」に設定
	_status = STATUS::NONE;
	// 再生時間の初期化
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	// 位置,向きの初期化
	vPos = VGet(-60, 0, 0);
	vDir = VGet(0, 0, -1);		// キャラモデルはデフォルトで-Z方向を向いている

	// 腰位置の設定
	_colSubY = 60.f;
}

void SAN::Input()
{
	int keyold1P = Key1P;
	Key1P = GetJoypadInputState(DX_INPUT_PAD1);
	Trg1P = (Key1P ^ keyold1P) & Key1P;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
}

void SAN::Update(Camera& cam) 
{
	Input();
	//int key = ApplicationMain::GetInstance()->GetKey1P();
	//int trg = ApplicationMain::GetInstance()->GetTrg1P();
	int key = Key1P;
	int trg = Trg1P;
	//std::unique_ptr<Camera> cam = std::make_unique<Camera>();

	// 処理前のステータスを保存しておく
	STATUS oldStatus = _status;
	// カメラの向いている角度を取得
	float sx = cam._vPos.x - cam._vTarget.x;
	float sz = cam._vPos.z - cam._vTarget.z;
	float camrad = atan2(sz, sx);

	// 移動方向を決める
	VECTOR v = { 0,0,0 };
	float mvSpeed = 6.f;
	//if (key & PAD_INPUT_RIGHT) { v.x = 1; }
	//if (key & PAD_INPUT_LEFT) { v.x = -1; }
	//if (key & PAD_INPUT_DOWN) { v.z = -1; }
	//if (key & PAD_INPUT_UP) { v.z = 1; }

	if (key & PAD_INPUT_DOWN) { v.x = 1; }
	if (key & PAD_INPUT_UP) { v.x = -1; }
	if (key & PAD_INPUT_LEFT) { v.z = -1; }
	if (key & PAD_INPUT_RIGHT) { v.z = 1; }
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
	hitPoly = MV1CollCheck_Line(_handleMap, _frameMapCollision,
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
		v.x = v.x / 2; v.y = v.y / 2; v.z = v.z / 2;
		cam._vPos = VAdd(cam._vPos, v);
		cam._vTarget = VAdd(cam._vTarget, v);
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
		Mplay_time += 0.5f;
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (Mattach_index != -1) {
			MV1DetachAnim(Mhandle, Mattach_index);
			Mattach_index = -1;
		}
		// ステータスに合わせてアニメーションのアタッチ
		switch (_status) {
		case STATUS::WAIT:
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "idle2"), -1, FALSE);
			break;
		case STATUS::WALK:
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "move2"), -1, FALSE);
			break;
		case STATUS::JUMP:
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "jump2"), -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		Mtotal_time = MV1GetAttachAnimTotalTime(Mhandle, Mattach_index);
		// 再生時間を初期化
		Mplay_time = 0.0f;
	}

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (Mplay_time >= Mtotal_time) {
		Mplay_time = 0.0f;
	}
}

void SAN::Render()
{
	// 再生時間をセットする
	MV1SetAttachAnimTime(Mhandle, Mattach_index, Mplay_time);

	// モデルを描画する
	{
		// 位置
		MV1SetPosition(Mhandle, vPos);
		// 向きからY軸回転を算出
		VECTOR vRot = { 0,0,0 };
		vRot.y = atan2(vDir.x * -1, vDir.z * -1);		// モデルが標準でどちらを向いているかで式が変わる(これは-zを向いている場合)
		MV1SetRotationXYZ(Mhandle, vRot);
		// 描画
		MV1SetScale(Mhandle, VGet(1.0f, 1.0f, 1.0f));
		MV1DrawModel(Mhandle);

		//ダメージ判定の描画
		DrawCapsule3D(VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
		DrawSphere3D(VGet(vPos.x, vPos.y + 50, vPos.z), 55, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);

		// コリジョン判定用ラインの描画
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));

		VECTOR v = ConvWorldPosToScreenPos(vPos);
		if (0.f <= v.z && v.z < 1.f)
		{
			DrawGraph(v.x, v.y, hphandle[0], true);
		}

	}
	//DrawFormatString(0, 260, GetColor(255, 255, 255), "%f, %f, %f", vPos.x, vPos.y, vPos.z);
}
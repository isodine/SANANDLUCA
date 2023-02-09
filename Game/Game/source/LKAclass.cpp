#include"LKAclass.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"

LKA::LKA()
	:Player()
{
}

LKA::~LKA()
{
}

void LKA::Initialize()
{
	Player::Initialize(mypH);

	// モデルデータのロード（テクスチャも読み込まれる）
	Mhandle = MV1LoadModel("res/Lka/Lka multimotion.mv1");

	// 位置,向きの初期化
	vPos = VGet(60, 20, 0);

	// 腰位置の設定
	_colSubY = 45.f;
}

void LKA::Input()
{
	int keyold2P = Key2P;
	Key2P = GetJoypadInputState(DX_INPUT_PAD2);
	Trg2P = (Key2P ^ keyold2P) & Key2P;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
}

void LKA::Update(Camera& cam)
{
	Input();
	int key = Key2P;
	int trg = Trg2P;

	Player::Update(mypH);

	// 処理前のステータスを保存しておく
	STATUS oldStatus = _status;
	// カメラの向いている角度を取得
	float sx = cam._vPos.x - cam._vTarget.x;
	float sz = cam._vPos.z - cam._vTarget.z;
	float camrad = atan2(sz, sx);

	// 移動方向を決める
	VECTOR v = { 0,0,0 };
	float mvSpeed = 6.f;

	if (key & PAD_INPUT_DOWN) { v.x = 1; }
	if (key & PAD_INPUT_UP) { v.x = -1; }
	if (key & PAD_INPUT_LEFT) { v.z = -1; }
	if (key & PAD_INPUT_RIGHT) { v.z = 1; }
	if (key & PAD_INPUT_1 && !(_status == STATUS::JUMP)) { _status = STATUS::JUMP; }

	if (_status == STATUS::JUMP) { Jump(cam); }
	// vをrad分回転させる
	float length = 0.f;
	if (VSize(v) > 0.f) { length = mvSpeed; }
	float rad = atan2(v.z, v.x);
	v.x = cos(rad + camrad) * length;
	v.z = sin(rad + camrad) * length;

	// 移動前の位置を保存
	oldPos = vPos;



	// 画面内にキャラクターが入っていないかどうかを描画する
//TRUEは入ってない、FALSEは入ってる
	if (CheckCameraViewClip(vPos) == TRUE)
	{
		// 画面外に出た。元の座標に戻す
		vPos = oldPos;
		v = { 0,0,0 };
	}

	// vの分移動
	this->vPos = VAdd(this->vPos, v);

	// カメラも移動する
	v.x = v.x / 2.0f; v.y = v.y / 2.0f; v.z = v.z / 2;
	cam._vPos = VAdd(cam._vPos, v);
	cam._vTarget = VAdd(cam._vTarget, v);

	// 移動した先でコリジョン判定
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	MV1_COLL_RESULT_POLY hitPolyfloor;
	MV1_COLL_RESULT_POLY hitPolywall;

	hitPolywall = MV1CollCheck_Line(_handleMap, frameMapCollisionwall,
		VAdd(vPos, VGet(0, _colSubY, -50)), VAdd(vPos, VGet(0, _colSubY, 500.f)));
	if (hitPolywall.HitFlag && (vPos.z + 30 >= hitPolywall.HitPosition.z))
	{
		float backwidth = hitPolywall.HitPosition.z - vPos.z + 30;
		float subX = vPos.x - oldPos.x;
		float subZ = vPos.z - oldPos.z;
		vPos.x = oldPos.x/*- subX*/;
		vPos.z = oldPos.z/*- subZ*/;

		cam._vPos.x -= subX / 2;
		cam._vPos.z -= subZ / 2;
		cam._vTarget.x -= subX / 2;
		cam._vTarget.z -= subZ / 2;
		v = { 0,0,0 };
	}

	// 主人公の腰位置から下方向への直線
	hitPolyfloor = MV1CollCheck_Line(_handleMap, frameMapCollisionfloor,
		VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)));

	hitPolyDim = MV1CollCheck_Capsule(_handleMap, frameMapCollisionfloor,
		VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f);
	if (hitPolyDim.HitNum >= 1)
	{
		// 当たった
		if (vPos.y < hitPolyfloor.HitPosition.y)
		{
			_status = STATUS::WAIT;
			throughtime = 0.0f;
			float minusY = vPos.y;
			// 当たったY位置をキャラ座標にする
			vPos.y = hitPolyfloor.HitPosition.y - 0.5f;
			cam._vPos.y += (vPos.y - minusY) / 2;
			cam._vTarget.y += (vPos.y - minusY) / 2;
		}
	}
	else {
		// 当たらなかった。元の座標に戻す
		freeFall(cam);
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
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "jamp2"), -1, FALSE);
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

void LKA::Render()
{
	Player::Render(mypH);

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
		MV1DrawModel(Mhandle);

		//ダメージ判定の描画
		DrawCapsule3D(VGet(vPos.x, vPos.y + 30, vPos.z), VGet(vPos.x, vPos.y + 75, vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
		DrawSphere3D(VGet(vPos.x, vPos.y + 50, vPos.z), 55, 8, GetColor(0, 0, 255), GetColor(255, 255, 255), FALSE);

		// コリジョン判定用ラインの描画
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, -50)), VAdd(vPos, VGet(0, _colSubY, 500.f)), GetColor(255, 0, 0));

	}
	int x = 0, y = 106, size = 16;
	SetFontSize(size);
	switch (_status)
	{
	case Player::STATUS::WAIT:
		DrawFormatString(x, y, GetColor(255, 0, 0), "Lka states = WAIT");
		break;
	case Player::STATUS::WALK:
		DrawFormatString(x, y, GetColor(255, 0, 0), "Lka states = WALK");
		break;
	case Player::STATUS::JUMP:
		DrawFormatString(x, y, GetColor(255, 0, 0), "Lka states = JUMP");
		break;
	}
}
void LKA::Jump(Camera& cam)
{
	if (throughtime == 0.f) { height = 10.f; }
	vPos.y += height;
	cam._vPos.y += height / 2;
	cam._vTarget.y += height / 2;
}

void LKA::freeFall(Camera& cam)
{
	vPos.y -= throughtime;
	cam._vPos.y -= throughtime / 2;
	cam._vTarget.y -= throughtime / 2;
	throughtime += 0.5f;
}
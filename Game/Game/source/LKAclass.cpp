#include"LKAclass.h"
#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"

LKA::LKA()
	:Player()
{
	SetType(false);
}

LKA::~LKA()
{
}

void LKA::Initialize()
{
	Player::Initialize();
	// モデルデータのロード（テクスチャも読み込まれる）
	Mhandle = MV1LoadModel("res/01_Character_Model/Lka_2023_0222/Lka_Fullmotion.mv1");
	hpgaugehandle[0] = LoadGraph("res/Lka/HP_lka_6.png");
	hpgaugehandle[1] = LoadGraph("res/Lka/HP_lka_5.png");
	hpgaugehandle[2] = LoadGraph("res/Lka/HP_lka_4.png");
	hpgaugehandle[3] = LoadGraph("res/Lka/HP_lka_3.png");
	hpgaugehandle[4] = LoadGraph("res/Lka/HP_lka_2.png");
	hpgaugehandle[5] = LoadGraph("res/Lka/HP_lka_1.png");
	hphandle[0] = LoadGraph("res/lka_v2/UI_lka_v6.png");
	hphandle[1] = LoadGraph("res/lka_v2/UI_lka_v5.png");
	hphandle[2] = LoadGraph("res/lka_v2/UI_lka_v4.png");
	hphandle[3] = LoadGraph("res/lka_v2/UI_lka_v3.png");
	hphandle[4] = LoadGraph("res/lka_v2/UI_lka_v2.png");
	hphandle[5] = LoadGraph("res/lka_v2/UI_lka_v1.png");
	Mattach_index = -1;		// アニメーションアタッチはされていない
	// ステータスを「無し」に設定
	_status = STATUS::NONE;
	// 再生時間の初期化
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	// 位置,向きの初期化
	vPos = VGet(60, 0, 0);
	vDir = VGet(0, 0, -1);		// キャラモデルはデフォルトで-Z方向を向いている

	// 腰位置の設定
	_colSubY = 60.f;
	oldcount = GetNowCount();

	_colSubY = 45.f;
	HP = 6;
}

void LKA::Input()
{
	int keyold2P = Key2P;
	Key2P = GetJoypadInputState(DX_INPUT_PAD2);
	Trg2P = (Key2P ^ keyold2P) & Key2P;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	key = Key2P;
	trg = Trg2P;
}

void LKA::Update()
{
	Player::Update();
}

void LKA::Render()
{
	Player::Render();
}
//	void LKA::Jump()
//	{
//		if (throughtime == 0.f) { height = 10.f; }
//		vPos.y += height;
//	}
//
//void LKA::freeFall()
//{
//	vPos.y -= throughtime;
//	throughtime += 0.5f;
//}
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
			Mattach_index = MV1AttachAnim(Mhandle, MV1GetAnimIndex(Mhandle, "walk2"), -1, FALSE);
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
	if (damage.SanHitFlag == true) { oldcount = GetNowCount(); }
}

void LKA::Render(Damage& damage) {
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
		DrawLine3D(VAdd(vPos, VGet(0, _colSubY, 0)), VAdd(vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));
		VECTOR v = ConvWorldPosToScreenPos(vPos);
		if (0.f <= v.z && v.z < 1.f)
		{
			if (damage.LkaHP == 6)
			{
				DrawGraph(0, 880, hpgaugehandle[0], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[0], true);
				}
			}
			if (damage.LkaHP == 5)
			{
				DrawGraph(0, 880, hpgaugehandle[1], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[1], true);
				}
			}
			if (damage.LkaHP == 4)
			{
				DrawGraph(0, 880, hpgaugehandle[2], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[2], true);
				}
			}
			if (damage.LkaHP == 3)
			{
				DrawGraph(0, 880, hpgaugehandle[3], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[3], true);
				}
			}
			if (damage.LkaHP == 2)
			{
				DrawGraph(0, 880, hpgaugehandle[4], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[4], true);
				}
			}
			if (damage.LkaHP == 1)
			{
				DrawGraph(0, 880, hpgaugehandle[5], true);
				auto nowcount = GetNowCount();
				if (nowcount - oldcount < 2000)
				{
					DrawGraph(v.x - 125, v.y, hphandle[5], true);
				}
			}
		}
	}
}
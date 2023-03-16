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

void LKA::Update(Damage& damage)
{
	Player::Update();
	if (damage.LkaHitFlag == true) { oldcount = GetNowCount(); }
	lkahitflag = false;
}

void LKA::Render(Damage& damage)
{
	Player::Render();
	VECTOR v = ConvWorldPosToScreenPos(vPos);
	if (0.f <= v.z && v.z < 1.f)
	{
		if (Player::HP == 6)
		{
			DrawGraph(1120, 880, hpgaugehandle[0], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[0], true);
				lkahitflag = true;
			}
		}
		if (Player::HP == 5)
		{
			DrawGraph(1120, 880, hpgaugehandle[1], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[1], true);
				lkahitflag = true;
			}
		}
		if (Player::HP == 4)
		{
			DrawGraph(1120, 880, hpgaugehandle[2], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[2], true);
				lkahitflag = true;
			}
		}
		if (Player::HP == 3)
		{
			DrawGraph(1120, 880, hpgaugehandle[3], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[3], true);
				lkahitflag = true;
			}
		}
		if (Player::HP == 2)
		{
			DrawGraph(1120, 880, hpgaugehandle[4], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[4], true);
				lkahitflag = true;
			}
		}
		if (Player::HP == 1)
		{
			DrawGraph(1120, 880, hpgaugehandle[5], true);
			auto nowcount = GetNowCount();
			if (nowcount - oldcount < 2000)
			{
				DrawGraph(v.x - 125, v.y, hphandle[5], true);
				lkahitflag = true;
			}
		}
	}
}

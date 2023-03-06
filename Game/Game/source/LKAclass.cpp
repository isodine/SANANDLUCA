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
	Mhandle = MV1LoadModel("res/Lka_2023_0222/Lka_Fullmotion.mv1");

	// 位置,向きの初期化
	vPos = VGet(60, 20, 0);
	//vPos = VGet(-60, 300, 0);
	// 腰位置の設定
	_colSubY = 45.f;
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
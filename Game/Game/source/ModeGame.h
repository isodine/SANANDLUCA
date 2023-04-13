#pragma once

#include "appframe.h"
#include "Player.h"
#include "SANclass.h"
#include "LKAclass.h"
#include "Damage.h"
#include "timer.h"
#include "Gimmick.h"
#include "sancircle.h"
#include "lkacircle.h"
#include "sanheal.h"
#include "lkacircle.h"
#include "IronDoor.h"
#include "Electrode.h"
#include "Elevator.h"
#include "Tube.h"
#include "BossSwamp.h"
#include "timer.h"
#include "ModeGameOver.h"

#include <string>
#include <memory>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

// 計算用マクロ
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )




// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	ModeGame();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();


	// カメラ
	Camera _cam;


	// 3Dモデル描画用
	//int _handle;
	//int _attach_index;
	//float _total_time;
	//float _play_time;
	VECTOR _vPos;	// 位置
	VECTOR _vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）

	// マップ用
	int _handleMap;//ステージのハンドル
	int _handleSkySphere;//スカイスフィアのハンドル
	int frameMapCollisionfloor;//床の当たり判定用のフレームの番号
	int frameMapCollisionwall;//壁の当たり判定用のフレームの番号
	int frameMapCollisiongoalSAN;//サンのゴール用のフレームの番号
	int frameMapCollisiongoalLKA;//ルカのゴール用のフレームの番号



	int LightHandle;
	int MaskHandle;

	// デバッグ用
	bool	_bViewCollision;

	//ジャンプ処理用
	float throughtime;
	float height;

	int Grhandle[20];
	int gameovercount;
	int gamestartcount;
	//シャドウマップ用
	int ShadowMapHandle;

	VECTOR ShadowMapUpVec;
	VECTOR ShadowMapDownVec;

	//ゲームオーバー用
	bool Isgameover;
	bool gameoverchange;
	bool Isgamestart;

	//UVスクロール
	float _UVScroll_U, _UVScroll_V;

	//VOICE用
	bool modeStart = false;
	int VOICEstartSANLKA[6] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/06_Start/Lka_GO_Voice_01.wav"),
								LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/06_Start/Lka_GO_Voice_02.wav"),
								LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/06_Start/Lka_GO_Voice_03.wav"),
								LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/06_Start/San_GO_Voice_01.wav"),
								LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/06_Start/San_GO_Voice_02.wav"),
								LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/06_Start/San_GO_Voice_03.wav") };

public:
	Player player;
	SAN san;
	LKA lka;
	SanBomb sanbomb;
	LkaBomb lkabomb;
	Sancircle sancircle;
	Lkacircle lkacircle;
	Damage damage;
	Gimmick gimmick;
	//Slime slime;
	IronDoor irondoor;
	Electrode electrode;
	Elevator elevator;
	Tube tube;
	Timer timer;
	ModeGameOver gameover;
	std::vector<std::unique_ptr<Slime>> slimes;
	std::vector<std::unique_ptr<IronDoor>> irondoors;
	std::vector<std::unique_ptr<Tube>> tubes;
};

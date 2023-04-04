#pragma once
#include <memory>
#include <vector>
#include "appframe.h"

class PlayerBomb;
class Camera;
class Damage;
class Gimmick;

class Player
{
public:
	enum Type
	{
		San,
		Lka
	};
	Type mypH;
	PlayerBomb* _bomb;
	Camera* _camera;
	Damage* _damage;
	ModeBase* base;
	Gimmick* _gimmick;

	void SetBomb(PlayerBomb* bomb);
	void SetCamera(Camera* camera);
	void SetDamage(Damage* damage);
	void SetGimmick(Gimmick* gimmick);
	void SetType(bool isSan);

	Player();
	~Player();
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Jump();
	virtual void freeFall();
	void charJump();
	virtual void Input();
	void UpdateCollision();

	int key;
	int trg;
	int stageHandle;
	int ironDoorHandle;
	int elevatorHnadle;
	int tubeHandle[3];
	int floorCol;
	int wallCol;
	int goalColSAN;
	int goalColLKA;
	int ironDoorCol;
	int elevatorCol;
	int tubeCol;

public:
	//当たり判定用
	MV1_COLL_RESULT_POLY hitPoly1;
	MV1_COLL_RESULT_POLY hitPoly2;

	MV1_COLL_RESULT_POLY_DIM hitPolyDimSAN;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimLKA;

	enum class STATUS {
		NONE,
		WAIT,
		WALK,
		JUMP,
		DAMAGE,
		CHARGE,
		ATTACK,
		DOWN,
		_EOT_
	};
	STATUS _status;
	STATUS oldStatus;
	//Camera _cam;

	//std::unique_ptr<Camera> cam = std::make_unique<Camera>();

	int Key1P, Key2P;
	int Trg1P, Trg2P;


	// 3Dモデル描画用
	int Mhandle;
	int Mattach_index;
	float Mtotal_time;
	float Mplay_time;
	VECTOR vPos;	// 位置
	VECTOR oldPos;  //前の位置
	VECTOR vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）

	//ボム関連用
	enum Attack
	{
		None,
		Pop,
		Keep,
		Throw,
		Dead
	};
	Attack attack;

	bool OnBalance;  //天秤に乗っているかどうか
	void SetOnBalance(bool on) { OnBalance = on; }

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	MV1_COLL_RESULT_POLY hitPolyfloor;

	//SE用
	//アウトゲーム

	int VOICEtutorialSAN;
	int VOICEtutorialLKA;

	int VOICEpose[2] = { LoadSoundMem("res/06_Sound/02_Voice/00_Out_Game/04_Pose/San_Pose_Voice_01.wav"),
		                 LoadSoundMem("res/06_Sound/02_Voice/00_Out_Game/04_Pose/Lka_Pose_Voice_01.wav")};

	int VOICEquitSAN;
	int VOICEquitLKA;

	//インゲーム
	int SEjump;

	int VOICEjumpSAN[4] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_01.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_02.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_03.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_04.wav") };

	int VOICEjumpLKA[4] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_01.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_02.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_03.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_04.wav") };

	int VOICEthrowBombSAN[3] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/San/San_bomb_Voice_01.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/San/San_bomb_Voice_02.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/San/San_bomb_Voice_03.wav") };

	int VOICEthrowBombLKA[3] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/Lka/Lka_bomb_Voice_01.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/Lka/Lka_bomb_Voice_02.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/Lka/Lka_bomb_Voice_03.wav") };

	int VOICEdeathSAN = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/04_Game_Over/San/San_Game_Over_Voice_01.wav");    //パンを設定して
	int VOICEdeathLKA = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/04_Game_Over/Lka/Lka_Game_Over_Voice_01.wav");    //同時に再生する

	int VOICEclearSAN = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/05_Game_Clear/San/San_Game_Clear_Voice_01.wav");    //〃
	int VOICEclearLKA = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/05_Game_Clear/Lka/Lka_Game_Clear_Voice_01.wav");    //〃

	//ジャンプ処理用
	float throughtime;
	float height;

	bool motionRes = false;
	int HP;
	bool goal = false;

	int Playercenter; //プレイヤーの中心をとる
	int Playerhead; //プレイヤーの頭上をとる
	float Playerbombsize;
	float Playercirclesize;

	void Landing(float HitYPos);

	//デバッグ表示用
	bool debagMode = false;
	bool viewCollision = false;
	bool viewValue = false;

	
};
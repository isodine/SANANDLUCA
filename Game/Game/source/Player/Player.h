/**
 * @file player.h
 * @brief プレイヤーのベースクラス
 * @author 磯島武尊
 * @date December 2022
 */

#pragma once
#include <memory>
#include <vector>
#include "appframe.h"

class PlayerBomb;
class Camera;
class Damage;
class Gimmick;
class IronDoor;

//プレイヤー共通のクラス
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
	//初期化処理
	virtual void Initialize();
	//更新処理
	virtual void Update(std::vector<std::unique_ptr<IronDoor>>* irondoors);
	//削除処理
	virtual void Terminate();
	//描画処理
	virtual void Render();
	//ジャンプ処理
	virtual void Jump();
	//自由落下処理
	virtual void freeFall();
	//操作取得
	virtual void Input();

	void UpdateCollision();
	//ノックバック処理
	virtual void KnockBack();

	int key;
	int trg;
	int stageHandle;//ステージのハンドル
	int ironDoorHandle;//鉄扉のハンドル
	int elevatorHnadle;//エレベーターのハンドル
	int tubeHandle[3];//T字パイプの数だけハンドルの配列を作る
	int floorCol;//床の当たり判定用のコリジョン
	int wallCol;//壁の当たり判定用のコリジョン
	int goalColSAN;//サンのゴールの当たり判定用コリジョン
	int goalColLKA;//ルカのゴールの当たり判定用コリジョン
	int ironDoorCol;//
	int elevatorCol;//
	int tubeCol[3];//T字パイプの数だけ当たり判定の配列を作る
	int pushCircle;//パイプの押し出しおよび当たり判定のための半径

	VECTOR tubeLineLeft[3];//当たり判定の線をとるための左側の点
	VECTOR tubeLineRight[3];//当たり判定の線をとるための右側の点
	VECTOR tubeLineCenter[3];//当たり判定の線をとるための中心の点
	VECTOR tubeLineFront[3];//当たり判定の線をとるための手前の点
	VECTOR hitPos;//パイプと当たった場所
	VECTOR hitLine;//T字パイプと当たった場所にある法線

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

	int Key1P, Key2P;
	int Trg1P, Trg2P;


	// 3Dモデル描画用
	int Mhandle;		//モデルデータ
	int Mattach_index;	//モデルのアニメーションアタッチ番号
	int BackCount;
	float Mtotal_time;	//モデルのアニメーションの総再生時間
	float Mplay_time;	//モデルのアニメーションの経過時間
	VECTOR vPos;		//位置
	VECTOR oldPos;		//前の位置
	VECTOR vDir;		//向き
	VECTOR v;
	VECTOR knockBackDir;//ノックバックする向き
	float _colSubY;		// コリジョン判定時のY補正(腰位置）

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
	// 移動した先でコリジョン判定
	MV1_COLL_RESULT_POLY_DIM hitPolyDimfloor;
	MV1_COLL_RESULT_POLY hitPolyfloor;
	MV1_COLL_RESULT_POLY hitPolywallback;
	MV1_COLL_RESULT_POLY hitPolywallside;
	MV1_COLL_RESULT_POLY hitPolygoalSAN;
	MV1_COLL_RESULT_POLY hitPolygoalLKA;
	MV1_COLL_RESULT_POLY hitPolyIronDoor;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimElevator;
	MV1_COLL_RESULT_POLY hitPolyElevator;
	MV1_COLL_RESULT_POLY_DIM hitPolyTube;

	bool hitDoor = false;

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
	float throughtime;			//ジャンプ中の落下値
	float height;				//ジャンプの上昇値

	bool motionRes = false;
	int HP;
	bool goal = false;			//TRUEならゴールした

	int Playercenter;			//プレイヤーの中心をとる
	int Playerhead;				//プレイヤーの頭上をとる
	float Playerbombsize;
	float Playercirclesize;

	void Landing(float HitYPos);//接地処理

	//デバッグ表示用
	bool debagMode = false;
	bool viewCollision = false;
	bool viewValue = false;

	
};

#include "appframe.h"
#include "Player.h"
#include "SANclass.h"
#include "LKAclass.h"
#include "Damage.h"
#include "Sanbomb.h"
#include "Lkabomb.h"
#include "sancircle.h"

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

	// マップ用
extern int _handleMap;
extern int _handleSkySphere;
extern int _frameMapCollision;

// カメラ
class Camera {
public:
	VECTOR	_vPos;					// 位置
	VECTOR	_vTarget;				// 距離
	float	_clipNear, _clipFar;	// クリップ
};

// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	void charJump();
	void bombthrow();

	// カメラ
	Camera	_cam;
	

	// 3Dモデル描画用
	int _handle;
	int _model;
	int _attach_index;
	float _total_time;
	float _play_time;
	VECTOR _vPos;	// 位置
	VECTOR _vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）

	int LightHandle;

	// デバッグ用
	bool	_bViewCollision;

	//ジャンプ処理用
	float throughtime;
	float height;

	//float _throw;
	//float _hight;
	//int _isthrow = 0;
public:
	std::vector<std::unique_ptr<Player>> sanlka;
	Player player;
	SAN san;
	LKA lka;
	Damage damage;
	Sanbomb sanbomb;
	Lkabomb lkabomb;
	Sancircle sancircle;

////エフェクシア
//protected:
//	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
//	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
//	int oldcount;
//	float PlayTime = 0.0f;
 int   _gKeyEf, _gTrgEf,_KeyEf,_TrgEf;
//	int _isEffect = 0;
//
//	// エフェクト位置
//	float _position_x;
//	float _position_y;
//	float _position_z;

};

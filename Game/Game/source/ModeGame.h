
#include "appframe.h"
#include "Player.h"
#include "SANclass.h"
#include "LKAclass.h"
#include "Damage.h"
#include "timer.h"
#include "gimmick.h"
#include "Slime.h"

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
extern int frameMapCollisionfloor;
extern int frameMapCollisionwall;

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
	ModeGame();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	void charJump();

	// カメラ
	Camera _cam;
	

	// 3Dモデル描画用
	int _handle;
	int _attach_index;
	float _total_time;
	float _play_time;
	VECTOR _vPos;	// 位置
	VECTOR _vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）

	int LightHandle;
	int MaskHandle;

	// デバッグ用
	bool	_bViewCollision;

	//ジャンプ処理用
	float throughtime;
	float height;

	//シャドウマップ用

	int ShadowMapHandle;

	VECTOR ShadowMapUpVec;
	VECTOR ShadowMapDownVec;

public:
	Player player;
	SAN san;
	LKA lka;
	SanBomb sanbomb;
	Damage damage;
	Gimmick gimmick;
	Slime slime;
	std::vector<std::unique_ptr<Slime>> slimes;
};

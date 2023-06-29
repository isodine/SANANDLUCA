#pragma once
#include "Bossrun.h"
#include "Bossattack.h"
#include "Bossdamage.h"
#include "Bossdown.h"

class Boss;

class ModeBoss : public ModeBase
{
public:
	ModeBoss();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	// カメラ
	Camera _cam;
	Camera _bossCam;

	// 3Dモデル描画用
	VECTOR _vPos;	// 位置
	VECTOR _vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）

	int _handleMap;
	int _handleSkySphere;
	int frameMapCollisionfloor;
	int frameMapCollisionwall;

	int Count;//仮

	int LightHandle;
	int MaskHandle;

	// デバッグ用
	bool	_bViewCollision;

	//ジャンプ処理用
	float throughtime;
	float height;

	//音楽、音関係用

public:
	std::vector<std::unique_ptr<Player>> sanlka;
	SAN san;
	LKA lka;
	SanBomb sanbomb;
	LkaBomb lkabomb;
	Sancircle sancircle;
	Lkacircle lkacircle;
	Damage damage;
	Boss boss;
	Bossrun bossrun;
	Bossattack bossattack;
	Bossdamage bossdamage;
	Bossdown bossdown;
	ModeGameOver gameover;
};

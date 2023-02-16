#pragma once
#include <memory>
#include <vector>

#include "appframe.h"

class Camera;

class Player
{
public:
	enum Type
	{
		San,
		Lka
	};
	Type mypH;

	Player();
	~Player();
	virtual void Initialize(Type mypH);
	virtual void Update(Type mypH);
	virtual void Render(Type mypH);
	void charJump();

public:


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
		Throw
	};
	Attack attack;

	bool OnBalance;  //天秤に乗っているかどうか
	void SetOnBalance(bool on) { OnBalance = on; }

	//SE用
	int SEjump;

	//ジャンプ処理用
	float throughtime;
	float height;

	bool motionRes = false;
	int HP;


	void Landing(float HitYPos);
};
#pragma once
#include <memory>
#include <vector>

#include "appframe.h"

class Camera;

class Player
{
public:
	Player();
	~Player();
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	void charJump();

public:
	enum Type
	{
		SAN,
		LKA
	};
	Type mypH;

	enum class STATUS {
		NONE,
		WAIT,
		WALK,
		JUMP,
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
	VECTOR vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）

	int HP;
	VECTOR myPos;

	//ジャンプ処理用
	float throughtime;
	float height;

};
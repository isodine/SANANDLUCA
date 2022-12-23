#pragma once
#include <memory>
#include <vector>
#include "appframe.h"

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


	// 3D���f���`��p
	int Mhandle;
	int Mattach_index;
	float Mtotal_time;
	float Mplay_time;
	VECTOR vPos;	// �ʒu
	VECTOR vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j

	int HP;
	VECTOR myPos;

	//�W�����v�����p
	float throughtime;
	float height;

};
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


	// 3D���f���`��p
	int Mhandle;
	int Mattach_index;
	float Mtotal_time;
	float Mplay_time;
	VECTOR vPos;	// �ʒu
	VECTOR oldPos;  //�O�̈ʒu
	VECTOR vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j

	//�{���֘A�p
	enum Attack
	{
		None,
		Pop,
		Keep,
		Throw
	};
	Attack attack;

	bool OnBalance;  //�V���ɏ���Ă��邩�ǂ���
	void SetOnBalance(bool on) { OnBalance = on; }

	//SE�p
	int SEjump;

	//�W�����v�����p
	float throughtime;
	float height;

	bool motionRes = false;
	int HP;


	void Landing(float HitYPos);
};
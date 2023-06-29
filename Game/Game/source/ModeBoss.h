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

	// �J����
	Camera _cam;
	Camera _bossCam;

	// 3D���f���`��p
	VECTOR _vPos;	// �ʒu
	VECTOR _vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j

	int _handleMap;
	int _handleSkySphere;
	int frameMapCollisionfloor;
	int frameMapCollisionwall;

	int Count;//��

	int LightHandle;
	int MaskHandle;

	// �f�o�b�O�p
	bool	_bViewCollision;

	//�W�����v�����p
	float throughtime;
	float height;

	//���y�A���֌W�p

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

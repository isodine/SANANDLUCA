#pragma once

class ModeBoss : public ModeBase
{
	//typedef ModeBase base;
public:
	ModeBoss();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	//void charJump();

	// �J����
	Camera _cam;


	// 3D���f���`��p
	int _handle;
	int _attach_index;
	float _total_time;
	float _play_time;
	VECTOR _vPos;	// �ʒu
	VECTOR _vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j

	int _handleMap;
	int _handleSkySphere;
	int frameMapCollisionfloor;
	int frameMapCollisionwall;

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
	Player player;
	SAN san;
	LKA lka;
	SanBomb sanbomb;
	Damage damage;
	Gimmick gimmick;
	Enemy enemy;
};

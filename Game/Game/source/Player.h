#pragma once
#include <memory>
#include <vector>

#include "appframe.h"

class PlayerBomb;
class Camera;
class Damage;
//class ModeBoss;

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

	void SetBomb(PlayerBomb* bomb);
	void SetCamera(Camera* camera);
	void SetDamage(Damage* damage);
	void SetType(bool isSan);
	
	Player();
	~Player();
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Jump();
	virtual void freeFall();
	void charJump();
	virtual void Input();

	int key;
	int trg;
	int stageHandle;
	int floorCol;
	int wallCol;

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
	//�A�E�g�Q�[��
	int VOICEtitleSAN;
	int VOICEtitleLKA;

	int VOICEplaySAN;
	int VOICEplayLKA;

	int VOICEtutorialSAN;
	int VOICEtutorialLKA;

	int VOICEposeSAN;
	int VOICEposeLKA;

	int VOICEquitSAN;
	int VOICEquitLKA;

	//�C���Q�[��
	int SEjump;

	int VOICEjumpSAN[4];
	int VOICEjumpLKA[4];

	int VOICEthrowBombSAN[3];
	int VOICEthrowBombLKA[3];

	int VOICEdamageSAN[2];
	int VOICEdamageLKA[2];

	int VOICEdeathSAN;
	int VOICEdeathLKA;

	int VOICEclearSAN;
	int VOICEclearLKA;

	int VOICEstartSANLKA[6];

	//�W�����v�����p
	float throughtime;
	float height;

	bool motionRes = false;
	int HP;


	void Landing(float HitYPos);


	//�f�o�b�O�\���p
	bool debagMode = false;
	bool viewCollision = false;
	bool viewValue = false;
};
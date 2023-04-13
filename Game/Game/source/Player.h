#pragma once
#include <memory>
#include <vector>
#include "appframe.h"

class PlayerBomb;
class Camera;
class Damage;
class Gimmick;
class IronDoor;

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
	Gimmick* _gimmick;

	void SetBomb(PlayerBomb* bomb);
	void SetCamera(Camera* camera);
	void SetDamage(Damage* damage);
	void SetGimmick(Gimmick* gimmick);
	void SetType(bool isSan);

	Player();
	~Player();
	virtual void Initialize();
	virtual void Update(std::vector<std::unique_ptr<IronDoor>>* irondoors);
	virtual void Update();
	virtual void Terminate();
	virtual void Render();
	virtual void Jump();
	virtual void freeFall();
	virtual void Input();
	void UpdateCollision();
	virtual void KnockBack();

	int key;
	int trg;
	int stageHandle;//�X�e�[�W�̃n���h��
	int ironDoorHandle;//�S���̃n���h��
	int elevatorHnadle;//�G���x�[�^�[�̃n���h��
	int tubeHandle[3];//T���p�C�v�̐������n���h���̔z������
	int floorCol;//���̓����蔻��p�̃R���W����
	int wallCol;//�ǂ̓����蔻��p�̃R���W����
	int goalColSAN;//�T���̃S�[���̓����蔻��p�R���W����
	int goalColLKA;//���J�̃S�[���̓����蔻��p�R���W����
	int ironDoorCol;//
	int elevatorCol;//
	int tubeCol[3];//T���p�C�v�̐����������蔻��̔z������
	int pushCircle;//�p�C�v�̉����o������ѓ����蔻��̂��߂̔��a

	VECTOR tubeLineLeft[3];//�����蔻��̐����Ƃ邽�߂̍����̓_
	VECTOR tubeLineRight[3];//�����蔻��̐����Ƃ邽�߂̉E���̓_
	VECTOR tubeLineCenter[3];//�����蔻��̐����Ƃ邽�߂̒��S�̓_
	VECTOR tubeLineFront[3];//�����蔻��̐����Ƃ邽�߂̎�O�̓_
	VECTOR hitPos;//�p�C�v�Ɠ��������ꏊ
	VECTOR hitLine;//T���p�C�v�Ɠ��������ꏊ�ɂ���@��

public:
	//�����蔻��p
	MV1_COLL_RESULT_POLY hitPoly1;
	MV1_COLL_RESULT_POLY hitPoly2;

	MV1_COLL_RESULT_POLY_DIM hitPolyDimSAN;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimLKA;

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
	STATUS oldStatus;
	//Camera _cam;

	//std::unique_ptr<Camera> cam = std::make_unique<Camera>();

	int Key1P, Key2P;
	int Trg1P, Trg2P;


	// 3D���f���`��p
	int Mhandle;
	int Mattach_index;
	int BackCount;
	float Mtotal_time;
	float Mplay_time;
	VECTOR vPos;	// �ʒu
	VECTOR oldPos;  //�O�̈ʒu
	VECTOR vDir;	// ����
	VECTOR v;
	VECTOR knockBackDir;//�m�b�N�o�b�N�������
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j

	//�{���֘A�p
	enum Attack
	{
		None,
		Pop,
		Keep,
		Throw,
		Dead
	};
	Attack attack;

	bool OnBalance;  //�V���ɏ���Ă��邩�ǂ���
	void SetOnBalance(bool on) { OnBalance = on; }

	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	// �ړ�������ŃR���W��������
	MV1_COLL_RESULT_POLY_DIM hitPolyDimfloor;
	MV1_COLL_RESULT_POLY hitPolyfloor;
	MV1_COLL_RESULT_POLY hitPolywallback;
	MV1_COLL_RESULT_POLY hitPolywallside;
	MV1_COLL_RESULT_POLY hitPolygoalSAN;
	MV1_COLL_RESULT_POLY hitPolygoalLKA;
	MV1_COLL_RESULT_POLY hitPolyIronDoor;
	MV1_COLL_RESULT_POLY_DIM hitPolyDimElevator;
	MV1_COLL_RESULT_POLY hitPolyElevator;
	MV1_COLL_RESULT_POLY_DIM hitPolyTube;

	bool hitDoor = false;

	//SE�p
	//�A�E�g�Q�[��

	int VOICEtutorialSAN;
	int VOICEtutorialLKA;

	int VOICEpose[2] = { LoadSoundMem("res/06_Sound/02_Voice/00_Out_Game/04_Pose/San_Pose_Voice_01.wav"),
		                 LoadSoundMem("res/06_Sound/02_Voice/00_Out_Game/04_Pose/Lka_Pose_Voice_01.wav")};

	int VOICEquitSAN;
	int VOICEquitLKA;

	//�C���Q�[��
	int SEjump;

	int VOICEjumpSAN[4] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_01.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_02.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_03.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/San/San_Jump_Voice_04.wav") };

	int VOICEjumpLKA[4] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_01.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_02.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_03.wav"),
							LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/01_Jump/Lka/Lka_Jump_Voice_04.wav") };

	int VOICEthrowBombSAN[3] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/San/San_bomb_Voice_01.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/San/San_bomb_Voice_02.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/San/San_bomb_Voice_03.wav") };

	int VOICEthrowBombLKA[3] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/Lka/Lka_bomb_Voice_01.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/Lka/Lka_bomb_Voice_02.wav"),
								 LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/02_Bomb/Lka/Lka_bomb_Voice_03.wav") };

	int VOICEdeathSAN = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/04_Game_Over/San/San_Game_Over_Voice_01.wav");    //�p����ݒ肵��
	int VOICEdeathLKA = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/04_Game_Over/Lka/Lka_Game_Over_Voice_01.wav");    //�����ɍĐ�����

	int VOICEclearSAN = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/05_Game_Clear/San/San_Game_Clear_Voice_01.wav");    //�V
	int VOICEclearLKA = LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/05_Game_Clear/Lka/Lka_Game_Clear_Voice_01.wav");    //�V

	//�W�����v�����p
	float throughtime;
	float height;

	bool motionRes = false;
	int HP;
	bool goal = false;//TRUE�Ȃ�S�[������

	int Playercenter; //�v���C���[�̒��S���Ƃ�
	int Playerhead; //�v���C���[�̓�����Ƃ�
	float Playerbombsize;
	float Playercirclesize;

	void Landing(float HitYPos);

	//�f�o�b�O�\���p
	bool debagMode = false;
	bool viewCollision = false;
	bool viewValue = false;

	
};
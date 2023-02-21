
#include "appframe.h"
#include "Player.h"
#include "SANclass.h"
#include "LKAclass.h"
#include "Damage.h"
#include "Sanbomb.h"
#include "Lkabomb.h"
#include "sancircle.h"

#include <string>
#include <memory>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

// �v�Z�p�}�N��
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

	// �}�b�v�p
extern int _handleMap;
extern int _handleSkySphere;
extern int _frameMapCollision;

// �J����
class Camera {
public:
	VECTOR	_vPos;					// �ʒu
	VECTOR	_vTarget;				// ����
	float	_clipNear, _clipFar;	// �N���b�v
};

// ���[�h
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();
	void charJump();
	void bombthrow();

	// �J����
	Camera	_cam;
	

	// 3D���f���`��p
	int _handle;
	int _model;
	int _attach_index;
	float _total_time;
	float _play_time;
	VECTOR _vPos;	// �ʒu
	VECTOR _vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j

	int LightHandle;

	// �f�o�b�O�p
	bool	_bViewCollision;

	//�W�����v�����p
	float throughtime;
	float height;

	//float _throw;
	//float _hight;
	//int _isthrow = 0;
public:
	std::vector<std::unique_ptr<Player>> sanlka;
	Player player;
	SAN san;
	LKA lka;
	Damage damage;
	Sanbomb sanbomb;
	Lkabomb lkabomb;
	Sancircle sancircle;

////�G�t�F�N�V�A
//protected:
//	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
//	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
//	int oldcount;
//	float PlayTime = 0.0f;
 int   _gKeyEf, _gTrgEf,_KeyEf,_TrgEf;
//	int _isEffect = 0;
//
//	// �G�t�F�N�g�ʒu
//	float _position_x;
//	float _position_y;
//	float _position_z;

};


#include "appframe.h"

#include <string>

// �v�Z�p�}�N��
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

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

protected:

	// �J����
	Camera	_cam;

	// 3D���f���`��p
	int _handle;
	int _attach_index;
	float _total_time;
	float _play_time;
	VECTOR _vPos;	// �ʒu
	VECTOR _vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j
	enum class STATUS {
		NONE,
		WAIT,
		WALK,
		JUMP,
		_EOT_
	};
	STATUS _status;

	// �}�b�v�p
	int _handleMap;
	int _handleSkySphere;
	int _frameMapCollision;


	// �f�o�b�O�p
	bool	_bViewCollision;

	//�W�����v�����p
	float throughtime;
	float height;

}; 

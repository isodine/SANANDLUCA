#include "Player.h"
//#include "ModeGame.h"
#include "Include.h"

int _handleMap;
int _handleSkySphere;
int frameMapCollisionfloor;
int frameMapCollisionwall;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Type myph)
{
	Mattach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�
	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	// �Đ����Ԃ̏�����
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���
	attack = Attack::None;
}

void Player::Update(Type mypH){}

void Player::Render(Type mypH){}

void Player::charJump() {
	height += 10.0f - throughtime;
	throughtime += 0.5f;
}


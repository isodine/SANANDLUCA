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

void Player::SetBomb(PlayerBomb* bomb)
{
	_bomb = bomb;
}
void Player::SetCamera(Camera* camera)
{
	_camera = camera;

}

void Player::SetDamage(Damage* damage)
{
	_damage = damage;
}

void Player::SetType(bool isSan)
{
	if (isSan)
	{
		mypH = San;
	}
	else
	{
		mypH = Lka;
	}
}


void Player::Initialize()
{
	Mattach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�
	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	// �Đ����Ԃ̏�����
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���
	attack = Attack::None;
	SEjump = LoadSoundMem("res/06_Sound/03_SE/ani_ta_biyon02.mp3");
}

void Player::Update() {}

void Player::Render() {}

void Player::charJump() {
	height += 10.0f - throughtime;
	throughtime += 0.5f;
}

void Player::Landing(float HitYPos) {
	_status = STATUS::WAIT;
	throughtime = 0.0f;
	//float minusY = vPos.y;
	// ��������Y�ʒu���L�������W�ɂ���
	vPos.y = HitYPos - 0.5f;
}

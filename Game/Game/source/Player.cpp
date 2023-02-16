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
	Mattach_index = -1;		// アニメーションアタッチはされていない
	// ステータスを「無し」に設定
	_status = STATUS::NONE;
	// 再生時間の初期化
	Mtotal_time = 0.f;
	Mplay_time = 0.0f;
	vDir = VGet(0, 0, -1);		// キャラモデルはデフォルトで-Z方向を向いている
	attack = Attack::None;
	SEjump = LoadSoundMem("res/06_Sound/03_SE/ani_ta_biyon02.mp3");
}

void Player::Update(Type mypH){}

void Player::Render(Type mypH){}

void Player::charJump() {
	height += 10.0f - throughtime;
	throughtime += 0.5f;
}

void Player::Landing(float HitYPos) {
	_status = STATUS::WAIT;
	throughtime = 0.0f;
	//float minusY = vPos.y;
	// 当たったY位置をキャラ座標にする
	vPos.y = HitYPos - 0.5f;
}

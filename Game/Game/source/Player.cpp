#include "Player.h"
#include "ModeGame.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{

}

void Player::Update(){}

void Player::Render(){}

void Player::charJump() {
	height += 10.0f - throughtime;
	throughtime += 0.5f;
	if (height == 1) {
		int kkkk = 1;
	}
}
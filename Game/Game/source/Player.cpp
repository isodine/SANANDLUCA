#include "Player.h"
#include "ModeGame.h"

int _handleMap;
int _handleSkySphere;
int _frameMapCollision;

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(Type myph)
{
}

void Player::Update(Type mypH){}

void Player::Render(Type mypH){}

void Player::charJump() {
	height += 10.0f - throughtime;
	throughtime += 0.5f;
}
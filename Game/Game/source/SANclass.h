#pragma once
#include"Player.h"

class SanBomb;

class SAN :public Player
{
public:
	SAN();
	~SAN();
	void Initialize();
	void Update(Camera& cam, SanBomb& sanB);
	void Render(SanBomb& sanB);
	void Input();
	void Jump(Camera& cam);
	void freeFall(Camera& cam);
};
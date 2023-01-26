#pragma once
#include"Player.h"

class LKA:public Player
{
public:
	LKA();
	~LKA();
	void Initialize();
	void Update(Camera& cam);
	void Render();
	void Input();
	void Jump(Camera& cam);
	void freeFall(Camera& cam);
};
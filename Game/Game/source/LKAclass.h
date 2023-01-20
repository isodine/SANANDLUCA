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

};
#pragma once
#include"Player.h"
#include "Gimmick.h"

class LKA:public Player, public Gimmick
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
#pragma once
#include"Player.h"

//class Gimmick;
class SAN:public Player
{
public:
	SAN();
	~SAN();
	void Initialize();
	void Update(Camera& cam);
	void Render();
	void Input();
	void Jump(Camera& cam);
	void freeFall(Camera& cam);

	//Gimmick gimmick;
};
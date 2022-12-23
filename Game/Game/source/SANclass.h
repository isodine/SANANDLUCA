#pragma once
#include"Player.h"

class SAN:public Player
{
public:
	SAN();
	~SAN();
	void Initialize()override;
	void Update();
	void Render()override;
	void Input();
private:

};
#pragma once
#include"Player.h"

class LKA:public Player
{
public:
	LKA();
	~LKA();
	void Initialize()override;
	void Update()override;
	void Render()override;
private:

};
#pragma once
#include"Player.h"
#include "Gimmick.h"

class LKA:public Player, public Gimmick
{
public:
	LKA();
	~LKA();
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Input() override;
	//void Jump();
	//void freeFall();
};
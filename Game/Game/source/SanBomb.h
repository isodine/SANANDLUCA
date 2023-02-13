#pragma once
class SanBomb:public PlayerBomb
{
public:
	SanBomb();
	~SanBomb();
	void Initialize();
	void Update();
	void Render();
	void Move();

};

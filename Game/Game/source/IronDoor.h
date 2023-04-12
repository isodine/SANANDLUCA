#pragma once
class IronDoor
{
public:
	IronDoor();
	~IronDoor();
	void Initialize();
	void Update(SanBomb& sanbomb);
	void Terminate();
	void Render();

	// 3Dƒ‚ƒfƒ‹•`‰æ—p
	int handle;
	VECTOR vPos;	// ˆÊ’u
	int handleCol;
	int handleIronDoor;
	int handleIronMeltDoor;
	bool melt = false;
};

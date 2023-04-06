#pragma once
class IronDoor
{
public:
	IronDoor();
	~IronDoor();
	void Initialize(bool type, VECTOR Pos);
	void Update(SanBomb& sanbomb, LkaBomb& lkabomb);
	void Render();
	void CollCheck(SAN& san, LKA& lka);

	// 3Dƒ‚ƒfƒ‹•`‰æ—p
	int handle;
	VECTOR vPos;	// ˆÊ’u
	int handleCol;
	int handleIronDoor;
	int handleIronMeltDoor;
	bool isSan = false;
	bool melt = false;
};

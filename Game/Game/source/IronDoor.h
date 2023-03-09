#pragma once
class IronDoor
{
public:
	IronDoor();
	~IronDoor();
	void Initialize();
	void Process();
	void Render();

	// 3Dƒ‚ƒfƒ‹•`‰æ—p
	int _handle;
	VECTOR _vPos;	// ˆÊ’u
	int ironDoorCol;
	int _handleIronDoor;
	int _handleIronMeltDoor;
	bool melt = false;
};

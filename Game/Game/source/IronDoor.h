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

	// 3D���f���`��p
	int handle;
	VECTOR vPos;	// �ʒu
	int handleCol;
	int handleIronDoor;
	int handleIronMeltDoor;
	bool melt = false;
};

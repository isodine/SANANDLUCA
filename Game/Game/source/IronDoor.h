#pragma once
class IronDoor
{
public:
	IronDoor();
	~IronDoor();
	void Initialize();
	void Process();
	void Render();

	// 3D���f���`��p
	int _handle;
	VECTOR _vPos;	// �ʒu
	int ironDoorCol;
	int _handleIronDoor;
	int _handleIronMeltDoor;
	bool melt = false;
};

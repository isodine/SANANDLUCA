IronDoor::IronDoor()
{
	handle = -1;

}

IronDoor::~IronDoor()
{
}

void IronDoor::Initialize()
{
	handleIronDoor = MV1LoadModel("res/02_Object_Model/Door/Iron/Iron/Irondoor.mv1");
	handleIronMeltDoor = MV1LoadModel("res/02_Object_Model/Door/Iron/Iron_melt/Irondoor_melt.mv1");
	MV1SetPosition(handleIronDoor, VGet(50.0f, 70.0f, 1200.0f));
	MV1SetPosition(handleIronMeltDoor, VGet(50.0f, 70.0f, 1200.0f));
	handle = handleIronDoor;
	handleCol = 0;
	MV1SetupCollInfo(handleIronDoor, handleCol, 2, 2, 2);
}

void IronDoor::Process(SanBomb& sanbomb)
{

	auto hitPolyDim{ MV1CollCheck_Sphere(handleIronDoor, handleCol, sanbomb.vPos, sanbomb.sphereSize) };

	if (hitPolyDim.HitNum >= 1)
	{
		MV1TerminateCollInfo(handleIronDoor, handleCol);
		handle = handleIronMeltDoor;
		MV1SetupCollInfo(handleIronMeltDoor, handleCol, 2, 2, 2);
		melt = true;
	}
	else {
		handle = handleIronDoor;
	}
}

void IronDoor::Render()
{
	MV1DrawModel(handle);
}

IronDoor::IronDoor()
{
}

IronDoor::~IronDoor()
{
}

void IronDoor::Initialize()
{
	_handleIronDoor = MV1LoadModel("res/02_Object_Model/Door/Iron/Iron/Irondoor.mv1");
	_handleIronMeltDoor = MV1LoadModel("res/02_Object_Model/Door/Iron/Iron_melt/Irondoor_melt.mv1");
	_handle = _handleIronDoor;
}

void IronDoor::Process()
{
	
}

void IronDoor::Render()
{

}

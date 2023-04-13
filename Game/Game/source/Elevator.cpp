Elevator::Elevator()
{
}

Elevator::~Elevator()
{
}

void Elevator::Initialize()
{
	handle = MV1LoadModel("res/02_Object_Model/Elevator/gimmick_elevator_01.mv1");
	handleCol = 0;
	vPos = VGet(500.f, 70.f, 1000.f);
	vPosfirst = VGet(500.f, 70.f, 1000.f);
	MV1SetScale(handle, VGet(5.0f, 5.0f, 5.0f));
	MV1SetPosition(handle, vPos);
}

void Elevator::Update(Electrode& electr)
{
	if (electr.change)
	{
		if (electr.isSan && !floating)
		{
			floating = true;
			moving = true;
		}
		else if (!(electr.isSan) && floating)
		{
			floating = false;
			moving = true;
		}
		else {}
	}
	Move();

}

void Elevator::Terminate() {
	MV1DeleteModel(handle);
}

void Elevator::Render()
{
	MV1SetPosition(handle, vPos);
	MV1DrawModel(handle);
}

void Elevator::Move()
{
	if (!moving) { return; }

	if (!(abs(vPos.y) == vPosfirst.y + upRange) && floating)
	{
		vPos = VAdd(vPos, speed);

		if(abs(vPos.y) == vPosfirst.y + upRange)
		{
			floating = true; moving = false; return;
		}
	}
	if (!(abs(vPos.y) == vPosfirst.y + downRange) && !floating)
	{
		vPos = VSub(vPos, speed);

		if (abs(vPos.y) == vPosfirst.y + downRange)
		{
			floating = false; moving = false;  return;
		}
	}
}
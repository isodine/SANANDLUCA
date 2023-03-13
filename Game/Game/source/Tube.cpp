Tube::Tube()
{
}

Tube::~Tube()
{
}

void Tube::Initialize(int Type)
{
	if (Type==0)
	{
		handle = MV1LoadModel("res/02_Object_Model/Elevator/gimmick_elevator_01.mv1");
		handleCol = 0;
		Type = TubeType::Neutrality;
		Dir = DirType::Front;
		vPos = VGet(500.f, 170.f, 1000.f);
		vPosfirst = VGet(500.f, 70.f, 1000.f);
		MV1SetScale(handle, VGet(5.0f, 5.0f, 5.0f));
		MV1SetPosition(handle, vPos);
	}
	else if (Type == 1)
	{
		handle = MV1LoadModel("res/02_Object_Model/Elevator/gimmick_elevator_01.mv1");
		handleCol = 0;
		Type = TubeType::Neutrality;
		Dir = DirType::Front;
		vPos = VGet(500.f, 170.f, 1000.f);
		vPosfirst = VGet(500.f, 70.f, 1000.f);
		MV1SetScale(handle, VGet(5.0f, 5.0f, 5.0f));
		MV1SetPosition(handle, vPos);
	}
	else if (Type == 2)
	{
		handle = MV1LoadModel("res/02_Object_Model/Elevator/gimmick_elevator_01.mv1");
		handleCol = 0;
		Type = TubeType::Neutrality;
		Dir = DirType::Front;
		vPos = VGet(500.f, 170.f, 1000.f);
		vPosfirst = VGet(500.f, 70.f, 1000.f);
		MV1SetScale(handle, VGet(5.0f, 5.0f, 5.0f));
		MV1SetPosition(handle, vPos);
	}
	else{}
}

void Tube::Update(Electrode& electr)
{
	if (electr.change)
	{
		if (electr.isSan && !Dir == DirType::Front)
		{
			spining = true;
			Dir = DirType::Left;
		}
		else if (!(electr.isSan) && Dir == DirType::Front)
		{
			spining = true;
			Dir = DirType::Left;
		}
		else {}
	}
	Spin();

}

void Tube::Render()
{
	MV1SetPosition(handle, vPos);
	MV1SetRotationXYZ(handle, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));
	MV1DrawModel(handle);
	//int x = 400, y = 0, size = 16;
	//SetFontSize(size);
	//floating ? DrawFormatString(x, y, GetColor(255, 0, 0), "floating == true ") : DrawFormatString(x, y, GetColor(255, 0, 0), "floating == false"); y += size;
	//moving ? DrawFormatString(x, y, GetColor(255, 0, 0), "moving == true ") : DrawFormatString(x, y, GetColor(255, 0, 0), "moving == false"); y += size;
}

void Tube::Spin()
{
	//if (!moving) { return; }

	//if (!(abs(vPos.y) == vPosfirst.y + upRange) && floating)
	//{
	//	vPos = VAdd(vPos, speed);

	//	if (abs(vPos.y) == vPosfirst.y + upRange)
	//	{
	//		floating = true; moving = false; return;
	//	}
	//}
	//if (!(abs(vPos.y) == vPosfirst.y + downRange) && !floating)
	//{
	//	vPos = VSub(vPos, speed);

	//	if (abs(vPos.y) == vPosfirst.y + downRange)
	//	{
	//		floating = false; moving = false;  return;
	//	}
	//}
}
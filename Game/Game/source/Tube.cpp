Tube::Tube()
{
}

Tube::~Tube()
{
}

void Tube::Initialize(int type, VECTOR Pos)
{
	if (type == 0)
	{
		handle = MV1LoadModel("res/02_Object_Model/Tube_gimmick/Tube_gimmick.mv1");
		handleCol = 0;
		Type = TubeType::Neutrality;
		Dir = DirType::Front;
		vPos = Pos;
		vDir = VGet(0, 0, 0);
		MV1SetPosition(handle, vPos);
	}
	else if (type == 1)
	{
		handle = MV1LoadModel("res/02_Object_Model/Tube_gimmick/Tube_gimmick_S.mv1");
		handleCol = 0;
		Type = TubeType::San;
		Dir = DirType::Right;
		vPos = Pos;
		vDir = VGet(0, 90, 0);
		MV1SetPosition(handle, vPos);
	}
	else if (type == 2)
	{
		handle = MV1LoadModel("res/02_Object_Model/Tube_gimmick/Tube_gimmick_L.mv1");
		handleCol = 0;
		Type = TubeType::Lka;
		Dir = DirType::Left;
		vPos = Pos;
		vDir = VGet(0, -90, 0);
		MV1SetPosition(handle, vPos);
	}
	else {}
}

void Tube::Update(Electrode& electr)
{
	switch (Type)
	{
	//case Tube::Neutrality:
	//	break;
	case Tube::San:
		if (electr.change)
		{
			if (electr.isSan && Dir == DirType::Front)
			{
				spining = true;
				Dir = DirType::Right;
			}
			else if (!(electr.isSan) && Dir == DirType::Right)
			{
				spining = true;
				Dir = DirType::Front;
			}
			else {}
		}
		break;
	case Tube::Lka:
		if (electr.change)
		{
			if (electr.isSan && Dir == DirType::Front)
			{
				spining = true;
				Dir = DirType::Left;
			}
			else if (!(electr.isSan) && Dir == DirType::Left)
			{
				spining = true;
				Dir = DirType::Front;
			}
			else {}
		}
		break;
	}

	Spin();

}

void Tube::Render()
{
	MV1SetPosition(handle, vPos);
	MV1SetRotationXYZ(handle, VGet(0.0f, vDir.y * DX_PI_F / 180.0f, 0.0f));
	MV1DrawModel(handle);
	//int x = 400, y = 0, size = 16;
	//SetFontSize(size);
	//switch (Type)
	//{
	//case Tube::San:
	//	Dir == DirType::Front ? DrawFormatString(x, y, GetColor(255, 0, 0), "DirType == Front ") : DrawFormatString(x, y, GetColor(255, 0, 0), "DirType == Right"); y += size;
	//	spining ? DrawFormatString(x, y, GetColor(255, 0, 0), "spining == true ") : DrawFormatString(x, y, GetColor(255, 0, 0), "spining == false"); y += size;
	//	break;
	//case Tube::Lka:
	//	x = 400, y = 32, size = 16;
	//	Dir == DirType::Front ? DrawFormatString(x, y, GetColor(255, 0, 0), "DirType == Front ") : DrawFormatString(x, y, GetColor(255, 0, 0), "DirType == Left"); y += size;
	//	spining ? DrawFormatString(x, y, GetColor(255, 0, 0), "spining == true ") : DrawFormatString(x, y, GetColor(255, 0, 0), "spining == false"); y += size;
	//	break;
	//}
}

void Tube::Spin()
{
	if (!spining) { return; }
	switch (Type)
	{
	case Tube::Neutrality:
		break;
	case Tube::San:
		if (!(abs(vDir.y) == rightRange) && Dir == DirType::Right)
		{
			vDir = VAdd(vDir, speed);

			if (abs(vDir.y) == rightRange)
			{
				Dir = DirType::Right; spining = false; return;
			}
		}
		if (!(abs(vDir.y) == frontRange) && Dir == DirType::Front)
		{
			vDir = VSub(vDir, speed);

			if (abs(vDir.y) == frontRange)
			{
				Dir = DirType::Front; spining = false; return;
			}
		}
		break;
	case Tube::Lka:
		if (!((vDir.y) == leftRange) && Dir == DirType::Left)
		{
			vDir = VSub(vDir, speed);

			if ((vDir.y) == leftRange)
			{
				Dir = DirType::Left; spining = false; return;
			}
		}
		if (!((vDir.y) == frontRange) && Dir == DirType::Front)
		{
			vDir = VAdd(vDir, speed);

			if ((vDir.y) == frontRange)
			{
				Dir = DirType::Front; spining = false; return;
			}
		}
		break;
	}


}
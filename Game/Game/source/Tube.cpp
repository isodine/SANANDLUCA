Tube::Tube()
{
}

Tube::~Tube()
{
}

void Tube::SetSanLka(SAN* _san, LKA* _lka) {
	san = _san;
	lka = _lka;
}

void Tube::Initialize(int type, VECTOR Pos)
{
	if (type == 0)
	{
		handle = MV1LoadModel("res/02_Object_Model/Tube_gimmick/Tube_gimmick.mv1");
		handleCol = 1;
		Type = TubeType::Neutrality;
		Dir = DirType::Front;
		vPos = Pos;
		vDir = VGet(0, 0, 0);
		MV1SetPosition(handle, vPos);
		MV1SetFrameVisible(handle, handleCol, FALSE);
	}
	else if (type == 1)
	{
		handle = MV1LoadModel("res/02_Object_Model/Tube_gimmick/Tube_S.mv1");
		handleCol = 4;
		Type = TubeType::San;
		Dir = DirType::Right;
		vPos = Pos;
		vDir = VGet(0, 90, 0);
		MV1SetPosition(handle, vPos);
		MV1SetFrameVisible(handle, handleCol, FALSE);
	}
	else if (type == 2)
	{
		handle = MV1LoadModel("res/02_Object_Model/Tube_gimmick/Tube_gimmick_L.mv1");
		handleCol = 1;
		Type = TubeType::Lka;
		Dir = DirType::Left;
		vPos = Pos;
		vDir = VGet(0, -90, 0);
		MV1SetPosition(handle, vPos);
		MV1SetFrameVisible(handle, handleCol, FALSE);
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
		MV1RefreshCollInfo(handle, handleCol);
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
		MV1RefreshCollInfo(handle, handleCol);
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
	int x = 400, y = 0, size = 16;
	SetFontSize(size);
}

void Tube::Spin()
{
	if (!spining) { return; }
	switch (Type)
	{
	case Tube::Neutrality:
		break;
	case Tube::San:
		MV1RefreshCollInfo(handle, handleCol);
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
		MV1RefreshCollInfo(handle, handleCol);
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
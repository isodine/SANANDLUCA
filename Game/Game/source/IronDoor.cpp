/**
 * @file IronDoor.cpp
 * @brief 鉄ドアのギミックを動かすプログラム
 * @author 磯島武尊
 * @date March 2023
 */

IronDoor::IronDoor()
{
	handle = -1;

}

IronDoor::~IronDoor()
{
}

void IronDoor::Initialize(bool type, VECTOR Pos)
{
	if (type)
	{
		handleIronDoor = MV1LoadModel("res/02_Object_Model/iron__Door/San_iron/Irondoor_S.mv1");
		handleIronMeltDoor = MV1LoadModel("res/02_Object_Model/iron__Door/San_iron_melt/Irondoor_melt_S.mv1");
	}
	if (!type)
	{
		handleIronDoor = MV1LoadModel("res/02_Object_Model/iron__Door/Alc_iron/Irondoor_melt_A.mv1");
		handleIronMeltDoor = MV1LoadModel("res/02_Object_Model/iron__Door/Alc_iron_melt/Irondoor_melt_A.mv1");
	}
/*	type ? handleIronDoor = MV1LoadModel("res/02_Object_Model/iron__Door/San_iron/Irondoor_S.mv1"),
			  handleIronMeltDoor = MV1LoadModel("res/02_Object_Model/iron__Door/Alc_iron_melt/Irondoor_melt_A.mv1") :
			  handleIronDoor = MV1LoadModel("res/02_Object_Model/iron__Door/Alc_iron/Irondoor_melt_A.mv1"),
			  handleIronMeltDoor = MV1LoadModel("res/02_Object_Model/iron__Door/San_iron_melt/Irondoor_melt_S.mv1");*/ /*Alc_iron_melt / Irondoor_melt_A*/
	MV1SetPosition(handleIronDoor, Pos);
	MV1SetPosition(handleIronMeltDoor, Pos);
	MV1SetScale(handleIronDoor, VGet(1.5f, 1.5f, 1.5f));
	MV1SetScale(handleIronMeltDoor, VGet(1.5f, 1.5f, 1.5f));
	handle = handleIronDoor;
	handleCol = 0;
	isSan = type;
	MV1SetupCollInfo(handleIronDoor, handleCol, 2, 2, 2);
}

void IronDoor::Update(SanBomb& sanbomb, LkaBomb& lkabomb)
{
	//if (melt) { return; }
	if(isSan)
	{
		auto hitPolyDim{ MV1CollCheck_Sphere(handleIronDoor, handleCol, lkabomb.vPos, lkabomb.sphereSize) };

		if (lkabomb.situation == lkabomb.PlayerBomb::Throw && hitPolyDim.HitNum >= 1)
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
	if (!isSan)
	{
		auto hitPolyDim{ MV1CollCheck_Sphere(handleIronDoor, handleCol, sanbomb.vPos, sanbomb.sphereSize) };

		if (sanbomb.situation == sanbomb.PlayerBomb::Throw && hitPolyDim.HitNum >= 1)
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
}

void IronDoor::Terminate(){
	MV1DeleteModel(handleIronDoor);
	MV1DeleteModel(handleIronMeltDoor);
}

void IronDoor::Render()
{
	MV1DrawModel(handle);
}

void IronDoor::CollCheck(SAN& san, LKA& lka)
{
	MV1_COLL_RESULT_POLY hitPolyIronDoor;

	hitPolyIronDoor = MV1CollCheck_Line(handle, handleCol,
		VAdd(san.vPos, VGet(0, san._colSubY, -50)), VAdd(san.vPos, VGet(0, san._colSubY, 500.f)));
	if (hitPolyIronDoor.HitFlag && (san.vPos.z + 30 >= hitPolyIronDoor.HitPosition.z)) {
		san.hitDoor = true;
	}
	else{
		san.hitDoor = false;
	}

	hitPolyIronDoor = MV1CollCheck_Line(handle, handleCol,
		VAdd(lka.vPos, VGet(0, lka._colSubY, -50)), VAdd(lka.vPos, VGet(0, lka._colSubY, 500.f)));
	if (hitPolyIronDoor.HitFlag && (lka.vPos.z + 30 >= hitPolyIronDoor.HitPosition.z)) {
		lka.hitDoor = true;
	}
	else {
		lka.hitDoor = false;
	}
}
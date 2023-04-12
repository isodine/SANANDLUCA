Electrode::Electrode()
{
}

Electrode::~Electrode()
{
}

void Electrode::Initialize(VECTOR Pos, bool is_san)
{
	handleSANelectrode = MV1LoadModel("res/02_Object_Model/electrode/electrode_S.mv1");
	handleLKAelectrode = MV1LoadModel("res/02_Object_Model/electrode/electrode_L.mv1");
	MV1SetPosition(handleSANelectrode, Pos);
	MV1SetPosition(handleLKAelectrode, Pos);
	is_san ? handle = handleSANelectrode : handle = handleLKAelectrode;
	handleCol = 0;
	isSan = is_san;
	MV1SetupCollInfo(handleSANelectrode, handleCol, 2, 2, 2);	//“–‚½‚è”»’è‚Í‚Ç‚¿‚ç‚©•Ð•û‚Ìƒ‚ƒfƒ‹‚Å‚¢‚¢
}

void Electrode::Update(SanBomb& sanbomb, LkaBomb& lkabomb)
{
	bool oldisSan = isSan;

	auto hitPolyDimSan{ MV1CollCheck_Sphere(handleSANelectrode, handleCol, sanbomb.vPos, sanbomb.sphereSize) };

	if (sanbomb.situation == sanbomb.PlayerBomb::Throw && hitPolyDimSan.HitNum >= 1)
	{
		handle = handleSANelectrode;
		isSan = true;
	}

	auto hitPolyDimLka{ MV1CollCheck_Sphere(handleLKAelectrode, handleCol, lkabomb.vPos, lkabomb.sphereSize) };

	if (lkabomb.situation == lkabomb.PlayerBomb::Throw && hitPolyDimLka.HitNum >= 1)
	{
		handle = handleLKAelectrode;
		isSan = false;
	}

	oldisSan == isSan ? change = false : change = true;

}

void Electrode::Render()
{
	MV1DrawModel(handle);
}
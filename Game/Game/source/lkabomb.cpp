LkaBomb::LkaBomb() :PlayerBomb()
{

}

LkaBomb::~LkaBomb()
{

}

void LkaBomb::Initialize(LKA& lka)
{
	vPos = VGet(lka.vPos.x, lka.vPos.y + 150, lka.vPos.z);

	mypH = Lka;
	situation = PlayerBomb::None;
}

void LkaBomb::Update(LKA& lka)
{
	int key = lka.Key2P;
	int trg = lka.Trg2P;


	if (lka.attack == Pop)
	{
		situation = PlayerBomb::Pop;
		bomblive = true;
	}

	if (lka.attack == Keep)
	{
		situation = PlayerBomb::Keep;
	}

	if (lka.attack == PlayerBomb::Throw)
	{
		situation = PlayerBomb::Throw;
	}

	switch (situation)
	{
	case PlayerBomb::None:
		break;
	case PlayerBomb::Pop:
		vPos = VGet(lka.vPos.x, lka.vPos.y + 150, lka.vPos.z);
		bomblive = true;
		if (sphereSize <= sphereMax)
		{
			sphereSize += 2;
		}
		else
		{
			situation = PlayerBomb::Keep;
		}
		break;
	case PlayerBomb::Keep:
		vPos = VGet(lka.vPos.x, lka.vPos.y + 150, lka.vPos.z);
		break;
	case PlayerBomb::Throw:
		Throw(lka);
		break;
	}
}

void LkaBomb::Render()
{
	DrawSphere3D(vPos, sphereSize, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);

}

void LkaBomb::Throw(LKA& lka)
{
	if (!firstdir)
	{
		vDir = VGet(0.f, 0.f, 0.f);
		vDir = VAdd(vDir, lka.vDir);
		//vDir.x = vDir.x * 2.f; vDir.y = vDir.y * 2.f; vDir.z = vDir.z * 2.f;
		firstdir = true;
	}
	vPos = VAdd(vPos, vDir);
	vPos.y -= count;
	vPos.y += decrement;
	count += 0.5f;
	if (vPos.y < 0) {
		BombReset();
	}
}


SanBomb::SanBomb():PlayerBomb()
{
}

SanBomb::~SanBomb(){}

void SanBomb::Initialize()
{
	vPos = VGet(0, 0, 0);

	mypH = San;
}

void SanBomb::Update()
{
	switch (situation)
	{
	case PlayerBomb::Pop:
		break;
	case PlayerBomb::Keep:
		break;
	case PlayerBomb::Throw:
		break;
	}
}

void SanBomb::Render()
{
	DrawSphere3D(vPos, 55, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
}
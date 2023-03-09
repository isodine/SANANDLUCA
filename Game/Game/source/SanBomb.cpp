SanBomb::SanBomb() :PlayerBomb()
{

}

SanBomb::~SanBomb() 
{

}

void SanBomb::Initialize(SAN& san)
{
	_effectResourceHandle = LoadEffekseerEffect("res/san_bomb_1.6_2/san_bomb_loop_01.efkefc");
	vPos = VGet(san.vPos.x, san.vPos.y + 150, san.vPos.z);
	
	mypH = San;
	situation = PlayerBomb::None;
}

void SanBomb::Update(SAN& san)
{
	int key = san.Key1P;
	int trg = san.Trg1P;


	if (san.attack == Pop)
	{
		situation = PlayerBomb::Pop;
		//bomblive = true;
	}

	if (san.attack == Keep)
	{
		situation = PlayerBomb::Keep;
	}

	if (san.attack == PlayerBomb::Throw)
	{
		situation = PlayerBomb::Throw;
	}

	switch (situation)
	{
	case PlayerBomb::None:
		break;
	case PlayerBomb::Pop:
		vPos = VGet(san.vPos.x, san.vPos.y + 150, san.vPos.z);
		if(bomblive == false)
		{
			_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
			// 再生中のエフェクトを移動する。
			SetPosPlayingEffekseer3DEffect(_playingEffectHandle, vPos.x, vPos.y, vPos.z);
			//_position_x += 0.2f;
		}
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
		vPos = VGet(san.vPos.x, san.vPos.y + 150, san.vPos.z);
		break;
	case PlayerBomb::Throw:
		Throw(san);
		break;
	}
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, vPos.x, vPos.y, vPos.z);
	if (vPos.y <= 0)
	{
		StopEffekseer3DEffect(_playingEffectHandle);
	}
}

void SanBomb::Render()
{
	//DrawSphere3D(vPos, sphereSize, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
	DrawEffekseer3D();
}

void SanBomb::Throw(SAN& san)
{
	if (!firstdir)
	{
		vDir = VGet(0.f, 0.f, 0.f);
		vDir = VAdd(vDir, san.vDir);
		vDir.x = vDir.x * 2.f; vDir.y = vDir.y * 2.f; vDir.z = vDir.z * 2.f;
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

void PlayerBomb::BombReset()
{
	bomblive = false;
	firstdir = false;
	sphereSize = 0.f;
	situation = PlayerBomb::None;
	count = 0.f;
}
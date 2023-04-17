LkaBomb::LkaBomb() :PlayerBomb()
{
}

LkaBomb::~LkaBomb()
{

}

void LkaBomb::Initialize(LKA& lka)
{
	_effectResourceHandle[0] = LoadEffekseerEffect("res/Lka_bomb_1.6_2/Lka_bomb_loop_01.efkefc");
	_effectResourceHandle[1] = LoadEffekseerEffect("res/Lka_bomb_explode/LKa_bomb_explode_effect.efkefc");

	vPos = VGet(lka.vPos.x, lka.vPos.y + lka.Playerhead, lka.vPos.z);

	mypH = Lka;
	situation = PlayerBomb::None;
	Isbombdead = false;
}

void LkaBomb::Update(LKA& lka)
{
	int key = lka.Key2P;
	int trg = lka.Trg2P;
	MV1_COLL_RESULT_POLY_DIM hitfloor;
	hitfloor = MV1CollCheck_Sphere(lka.stageHandle, lka.floorCol, vPos, 10.0f);

	if (lka.attack == Pop)
	{
		situation = PlayerBomb::Pop;
		//bomblive = true;
	}

	if (lka.attack == Keep)
	{
		situation = PlayerBomb::Keep;
	}

	if (lka.attack == PlayerBomb::Throw)
	{
		situation = PlayerBomb::Throw;
	}
	if (0 < hitfloor.HitNum)
	{
		BombReset();
		StopEffekseer3DEffect(_playingEffectHandle[0]);
		vPos = VGet(vPos.x, vPos.y, vPos.z);
		situation = PlayerBomb::Dead;
	}
	switch (situation)
	{
	case PlayerBomb::None:
		break;
	case PlayerBomb::Pop:
		vPos = VGet(lka.vPos.x, lka.vPos.y + lka.Playerhead, lka.vPos.z);
		if (bomblive == false)
		{
			_playingEffectHandle[0] = PlayEffekseer3DEffect(_effectResourceHandle[0]);
			// 再生中のエフェクトを移動する。
			SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], vPos.x, vPos.y, vPos.z);
			/*		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[0], 10.0f, 10.0f, 10.0f);*/
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
		vPos = VGet(lka.vPos.x, lka.vPos.y + lka.Playerhead, lka.vPos.z);
		break;
	case PlayerBomb::Throw:
		Throw(lka);
		break;
	case PlayerBomb::Dead:
		if (!Isbombdead)
		{
			_playingEffectHandle[1] = PlayEffekseer3DEffect(_effectResourceHandle[1]);
			// 再生中のエフェクトを移動する。
			SetPosPlayingEffekseer3DEffect(_playingEffectHandle[1], vPos.x, vPos.y, vPos.z);
			SetScalePlayingEffekseer3DEffect(_playingEffectHandle[1], 10.0f, 10.0f, 10.0f);
			PlaySoundFile("res/06_Sound/03_SE/san_lka_bomb.mp3", DX_PLAYTYPE_BACK);
		}
		Isbombdead = true;
		IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle[1]);
		Bombdead();
		break;
}
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], vPos.x, vPos.y, vPos.z);
}

void LkaBomb::Render()
{
	//DrawSphere3D(vPos, sphereSize, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
	DrawEffekseer3D();
}

void LkaBomb::Terminate(){
	DeleteEffekseerEffect(_effectResourceHandle[0]);
	DeleteEffekseerEffect(_effectResourceHandle[1]);
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
		bomblive = false;
		firstdir = false;
		sphereSize = 0.f;
		count = 0.f;
		StopEffekseer3DEffect(_playingEffectHandle[0]);
		situation = PlayerBomb::None;
	}

}

void LkaBomb::Bombdead()
{
	DrawEffekseer3D();
	if (IsPlaying == -1)
	{
		situation = PlayerBomb::None;
		Isbombdead = false;
		vPos = VGet(san.vPos.x, san.vPos.y + 150, san.vPos.z);
	}
}

void LkaBomb::BombReset()
{
	bomblive = false;
	firstdir = false;
	sphereSize = 0.f;
	situation = PlayerBomb::Dead;
	count = 0.f;
}

void LkaBomb::EffectReset()
{
	StopEffekseer3DEffect(_playingEffectHandle[0]);
	StopEffekseer3DEffect(_playingEffectHandle[1]);
}


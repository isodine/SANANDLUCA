PlayerBomb::PlayerBomb() {}
PlayerBomb::~PlayerBomb() {}

SanBomb::SanBomb() :PlayerBomb()
{
	_effectResourceHandle = LoadEffekseerEffect("res/san_bomb_1.6_2/san_bomb_loop_01.efkefc", 10.0f);
}

SanBomb::~SanBomb() {

	DeleteEffekseerEffect(_effectResourceHandle);

}

void SanBomb::Initialize(SAN& san)
{
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
		bomblive = true;
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

	if (_isthrow == 0)
	{
		vPos.x = san.vPos.x;
		vPos.y = san.vPos.y + 150;
		vPos.z = san.vPos.z;
	}
	if (trg & PAD_INPUT_6 && _isEffect == 0)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		// �Đ����̃G�t�F�N�g���ړ�����B
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, vPos.x, vPos.y, vPos.z);
		//_position_x += 0.2f;
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 0.1f, 0.1f, 0.1f);

		_isEffect = 1;

		oldcount = GetNowCount();
	}
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, vPos.x, vPos.y, vPos.z);
	UpdateEffekseer3D();
	if (oldcount > 0)
	{
		auto nowCount = GetNowCount();
		if (nowCount - oldcount >= 2000)
		{
			if (trg & PAD_INPUT_6 && _isEffect == 1)
			{
				_isthrow = 1;
			}
			if (_isthrow == 1)
			{
				Throw(san);
			}
			if (vPos.y <= 0)
			{
				_isEffect = 0;
				_isthrow = 0;
				oldcount = 0;
				BombReset();
				StopEffekseer3DEffect(_playingEffectHandle);
			}
		}
	}

	/*if (vPos.y <= 0)
	{
		BombReset();
	}*/
}

void SanBomb::Render()
{
	DrawSphere3D(vPos, sphereSize, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);

	Effekseer_Sync3DSetting();
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
}

void PlayerBomb::BombReset()
{
	bomblive = false;
	firstdir = false;
	sphereSize = 0.f;
	situation = PlayerBomb::None;
	count = 0.f;
}
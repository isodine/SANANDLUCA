#include"Bossdown.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeBoss.h"

Bossdown::Bossdown()
{
	_effectResourceHandle[0] = LoadEffekseerEffect("res/Beaker/Beaker_down01/Beaker_down01.efkefc");
	_effectResourceHandle[1] = LoadEffekseerEffect("res/Beaker/Beaker_down02/Beaker_down02.efkefc");
	IsPlaying[0] = -1;
	IsPlaying[1] = 0;
	downEfsize[0] = 500.0f;
	downEfsize[1] = 100.0f;
	Isdown = false;
}

Bossdown::~Bossdown()
{
}

void Bossdown::Update(Boss& boss)
{
	if (boss.type == Boss::BOSSTYPE::DOWN && IsPlaying[0] == -1)
	{
		_playingEffectHandle[0] = PlayEffekseer3DEffect(_effectResourceHandle[0]);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[0], downEfsize[0], downEfsize[0], downEfsize[0]);
	}
	IsPlaying[0] = IsEffekseer3DEffectPlaying(_playingEffectHandle[0]);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], boss.model.pos.x + 50, boss.model.pos.y, boss.model.pos.z + 50);
	if (boss.bossdownflag == true)
	{
		MV1DeleteModel(boss.noneHandle);
		MV1DeleteModel(boss.acidHandle);
		MV1DeleteModel(boss.alcaliHandle);
		_playingEffectHandle[1] = PlayEffekseer3DEffect(_effectResourceHandle[1]);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[1], downEfsize[1], downEfsize[1], downEfsize[1]);
		Isdown = true;
		boss.bossdownflag = false;
	}
	IsPlaying[1] = IsEffekseer3DEffectPlaying(_playingEffectHandle[1]);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[1], boss.model.pos.x, boss.model.pos.y, boss.model.pos.z);
	if (Isdown == true &&IsPlaying[1] == -1)
	{
		boss.downFlag = true;
	}
	UpdateEffekseer3D();
}

void Bossdown::Render()
{
	Effekseer_Sync3DSetting();
	DrawEffekseer3D();
}
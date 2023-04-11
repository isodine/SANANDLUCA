#include"Bossdown.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeBoss.h"

Bossdown::Bossdown()
{
	_effectResourceHandle = LoadEffekseerEffect("res/Beaker/Beaker_down02/Beaker_down02.efkefc");
	IsPlaying = 0;
	downEfsize = 400.0f;
	Isdown = false;
}

Bossdown::~Bossdown()
{
}

void Bossdown::Update(Boss& boss)
{
	if (boss.bossdownEf == true)
	{
		MV1DeleteModel(boss.noneHandle);
		MV1DeleteModel(boss.acidHandle);
		MV1DeleteModel(boss.alcaliHandle);
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, downEfsize, downEfsize, downEfsize);
		PlaySoundFile("res/06_Sound/03_SE/beaker_exprode.mp3", DX_PLAYTYPE_BACK);
		Isdown = true;
		boss.bossdownEf = false;
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, boss.model.pos.x, boss.model.pos.y, boss.model.pos.z);
	if (Isdown == true &&IsPlaying == -1)
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
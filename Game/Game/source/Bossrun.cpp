#include"Bossrun.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeBoss.h"

Bossrun::Bossrun()
{
	_effectResourceHandle = LoadEffekseerEffect("res/Beaker/Beaker_run02/Beaker_run02_effect.efkefc", 10.0f);
	runEfsize = 10.0f;
}
Bossrun::~Bossrun()
{

}

void Bossrun::Update(Boss& boss)
{
	Effekseer_Sync3DSetting();
	if (boss.type == Boss::BOSSTYPE::RUSH && IsPlaying == -1)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, boss.model.pos.x , boss.model.pos.y, boss.model.pos.z);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, runEfsize, runEfsize, runEfsize);
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle);
	 //再生中のエフェクトを移動する。

	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, boss.model.pos.x, boss.model.pos.y, boss.model.pos.z);
	SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0,boss.model.dir.y-(DX_PI_F/2.0f), 0);
	UpdateEffekseer3D();
}

void Bossrun::Render()
{

	DrawEffekseer3D();
}
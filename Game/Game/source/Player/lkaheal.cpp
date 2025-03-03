#include"lkaheal.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "GameMode/ModeGame.h"

Lkaheal::Lkaheal()
{
	_effectResourceHandle = LoadEffekseerEffect("res/Lka_heal01/Lka_heal01.efkefc", 10.0f);
	IsPlaying = -1;

}

Lkaheal::~Lkaheal()
{
}

void Lkaheal::Update(LKA& lka)
{
	if (IsPlaying == -1)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, lka.vPos.x, lka.vPos.y + 150, lka.vPos.z);
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, lka.vPos.x, lka.vPos.y, lka.vPos.z);
	UpdateEffekseer3D();
}

void Lkaheal::Render()
{
	Effekseer_Sync3DSetting();

	DrawEffekseer3D();
}
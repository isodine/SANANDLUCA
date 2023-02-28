#include"lkacircle.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Lkacircle::Lkacircle()
{
	_effectResourceHandle = LoadEffekseerEffect("res/Lka_heal/Lka_heal_start_.efkefc", 10.0f);
}

Lkacircle::~Lkacircle()
{
}

void Lkacircle::Update(LKA& lka)
{
	if (IsPlaying == -1)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, lka.vPos.x, lka.vPos.y + 150, lka.vPos.z);
		//_position_x += 0.2f;
		//SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 0.1f, 0.1f, 0.1f);
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, lka.vPos.x, lka.vPos.y, lka.vPos.z);
	//UpdateEffekseer3D();
}

void Lkacircle::Render()
{
	Effekseer_Sync3DSetting();

	DrawEffekseer3D();
}
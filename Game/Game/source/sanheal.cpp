#include"sanheal.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Sanheal::Sanheal()
{
	_effectResourceHandle = LoadEffekseerEffect("res/sun_heal01/sun_heal01.efkefc", 10.0f);
}

Sanheal::~Sanheal()
{
}

void Sanheal::Update(SAN& san)
{
	if (IsPlaying == -1)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, san.vPos.x, san.vPos.y + 150, san.vPos.z);
		//_position_x += 0.2f;
		//SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 0.1f, 0.1f, 0.1f);
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, san.vPos.x, san.vPos.y, san.vPos.z);
	UpdateEffekseer3D();
}

void Sanheal::Render()
{
	Effekseer_Sync3DSetting();

	DrawEffekseer3D();
}
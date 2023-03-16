#include"sancircle.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Sancircle::Sancircle()
{
	_effectResourceHandle = LoadEffekseerEffect("res/sun_heal/sun_heal_start_.efkefc", 10.0f);
	IsPlaying = -1;
}

Sancircle::~Sancircle()
{
}

void Sancircle::Update(SAN& san,LKA& lka)
{
	VECTOR ChIt;
	float LE;
	ChIt = VSub(san.vPos, lka.vPos);
	ChIt.y = 0.0f;
	LE = VSize(ChIt);
	if (LE <= 130.0f && IsPlaying == -1)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, san.vPos.x, san.vPos.y + san.Playercenter, san.vPos.z);
		//_position_x += 0.2f;
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, san.Playercirclesize, san.Playercirclesize, san.Playercirclesize);

	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, san.vPos.x, san.vPos.y + san.Playercenter, san.vPos.z);
	UpdateEffekseer3D();
}

void Sancircle::Render()
{
	Effekseer_Sync3DSetting();
	DrawEffekseer3D();
}
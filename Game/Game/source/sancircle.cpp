#include"sancircle.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Sancircle::Sancircle()
{
	_effectResourceHandle = LoadEffekseerEffect("res/sun_heal/sun_heal_start_.efkefc", 10.0f);
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
	if (LE <= 120.0f && IsPlaying == -1)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, san.vPos.x, san.vPos.y + 45, san.vPos.z);
		//_position_x += 0.2f;
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 0.75f, 0.75f, 0.75f);

	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, san.vPos.x, san.vPos.y + 45, san.vPos.z);
}

void Sancircle::Render()
{
	Effekseer_Sync3DSetting();
	DrawEffekseer3D();
}
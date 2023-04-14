#include"sancircle.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Sancircle::Sancircle()
{
	_effectResourceHandle[0] = LoadEffekseerEffect("res/sun_heal/sun_heal_start_.efkefc", 10.0f);
	_effectResourceHandle[1] = LoadEffekseerEffect("res/sun_heal/sun_heal_end_.efkefc", 10.0f);
	Iscircle = false;
	cautionHandle = LoadGraph("res/sun_heal/caution.png");
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
	if (LE <= 200.0f && IsPlaying == -1)
	{
		_playingEffectHandle[0] = PlayEffekseer3DEffect(_effectResourceHandle[0]);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], san.vPos.x, san.vPos.y + 45, san.vPos.z);
		//_position_x += 0.2f;
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[0], 0.75f, 0.75f, 0.75f);
		Iscircle = true;
	}
	if (LE > 200.0f && Iscircle == true)
	{
		StopEffekseer3DEffect(_playingEffectHandle[0]);
		_playingEffectHandle[1] = PlayEffekseer3DEffect(_effectResourceHandle[1]);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle[1], san.vPos.x, san.vPos.y + 45, san.vPos.z);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[1], 0.75f, 0.75f, 0.75f);
		//_position_x += 0.2f;
		Iscircle = false;
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle[0]);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], san.vPos.x, san.vPos.y + 45, san.vPos.z);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[1], san.vPos.x, san.vPos.y + 45, san.vPos.z);
	UpdateEffekseer3D();
}

void Sancircle::Render()
{
	Effekseer_Sync3DSetting();
	DrawEffekseer3D();
	if (Iscircle) {
		DrawGraph(590, 850, cautionHandle, false);
	}
}

void Sancircle::EffectReset()
{
	StopEffekseer3DEffect(_playingEffectHandle[0]);
	StopEffekseer3DEffect(_playingEffectHandle[1]);
}
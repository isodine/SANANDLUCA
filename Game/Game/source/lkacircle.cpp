#include"lkacircle.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Lkacircle::Lkacircle()
{
	IsPlaying = -1;
	_effectResourceHandle[0] = LoadEffekseerEffect("res/Lka_heal/Lka_heal_start_.efkefc", 10.0f);
	_effectResourceHandle[1] = LoadEffekseerEffect("res/Lka_heal/Lka_heal_end_.efkefc", 10.0f);
}

Lkacircle::~Lkacircle()
{
}

void Lkacircle::Update(SAN& san, LKA& lka)
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
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], lka.vPos.x, lka.vPos.y + 45, lka.vPos.z);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[0], 0.75f, 0.75f, 0.75f);
		Iscircle = true;
	}
	if (LE > 200.0f && Iscircle == true)
	{
		StopEffekseer3DEffect(_playingEffectHandle[0]);
		_playingEffectHandle[1] = PlayEffekseer3DEffect(_effectResourceHandle[1]);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle[1], lka.vPos.x, lka.vPos.y + 45, lka.vPos.z);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[1], 0.75f, 0.75f, 0.75f);
		//_position_x += 0.2f;
		Iscircle = false;
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle[0]);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], lka.vPos.x, lka.vPos.y + 45, lka.vPos.z);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[1], lka.vPos.x, lka.vPos.y + 45, lka.vPos.z);
}

void Lkacircle::Render()
{
	Effekseer_Sync3DSetting();

	DrawEffekseer3D();
}
#include"Bossdamage.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "GameMode/ModeBoss.h"

Bossdamage::Bossdamage()
{
	_effectResourceHandle = LoadEffekseerEffect("res/Beaker/Beaker_down01/Beaker_down01.efkefc");
	damageEfsize = 400.0f;
}

Bossdamage::~Bossdamage()
{
}

void Bossdamage::Update(Boss& boss)
{
	Effekseer_Sync3DSetting();
	if (boss.bosshitEf == true)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, damageEfsize, damageEfsize, damageEfsize);
		PlaySoundFile("res/06_Sound/03_SE/beaker_damage.mp3", DX_PLAYTYPE_BACK);
	}
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, boss.model.pos.x, boss.model.pos.y, boss.model.pos.z);
}

void Bossdamage::Render(Boss& boss)
{
	DrawEffekseer3D();
	boss.bosshitEf = false;
}

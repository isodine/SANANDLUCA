#include"Bossattack.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeBoss.h"

Bossattack::Bossattack()
{
	_effectResourceHandle[0] = LoadEffekseerEffect("res/Beaker/Beaker_attack02/Beaker_attack02_effect.efkefc");
	_effectResourceHandle[1] = LoadEffekseerEffect("res/Beaker/Beaker_attack01/Beaker_attack01_effect.efkefc");
	IsPlaying = -1;
	attackEfsize = 150.0f;
}

Bossattack::~Bossattack()
{
}

void Bossattack::Update(Boss&boss,Damage& damage)
{
	Effekseer_Sync3DSetting();
	if (boss.type == Boss::BOSSTYPE::CAPTURE && IsPlaying == -1 && (boss.sanhitEf== true || boss.lkahitEf == true))
	{
		_playingEffectHandle[0] = PlayEffekseer3DEffect(_effectResourceHandle[0]);
		_playingEffectHandle[1] = PlayEffekseer3DEffect(_effectResourceHandle[1]);
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], boss.model.pos.x, boss.model.pos.y, boss.model.pos.z);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle[0], attackEfsize, attackEfsize, attackEfsize);
	}
	IsPlaying = IsEffekseer3DEffectPlaying(_playingEffectHandle[1]);
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle[0], boss.model.pos.x, boss.model.pos.y + 1, boss.model.pos.z);
}

void Bossattack::Render(Boss& boss)
{
	DrawEffekseer3D();
	boss.sanhitEf = false;
	boss.lkahitEf = false;
}
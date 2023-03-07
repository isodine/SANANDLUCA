#include"Lkabomb.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Lkabomb::Lkabomb()
{
	_effectResourceHandle = LoadEffekseerEffect("res/Lka_bomb_1.6_2/Lka_bomb_loop_01.efkefc", 10.0f);
	oldcount = 0;
}

Lkabomb::~Lkabomb()
{
	DeleteEffekseerEffect(_effectResourceHandle);
}

void Lkabomb::Init()
{
}
void Lkabomb::Update(LKA& lka)
{
	int keyoldEf = _KeyEf;
	_KeyEf = GetJoypadInputState(DX_INPUT_PAD2);
	_TrgEf = (_KeyEf ^ keyoldEf) & _KeyEf;

	if (_isthrow == 0)
	{
		_position_x = lka.vPos.x;
		_position_y = lka.vPos.y + 150;
		_position_z = lka.vPos.z;
	}
	if (_TrgEf & PAD_INPUT_6 && _isEffect == 0)
	{
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
		// 再生中のエフェクトを移動する。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
		//_position_x += 0.2f;
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 0.1f, 0.1f, 0.1f);

		_isEffect = 1;

		oldcount = GetNowCount();


	}
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
	//UpdateEffekseer3D();


	if (oldcount > 0)
	{
		auto nowCount = GetNowCount();
		if (nowCount - oldcount >= 2000)
		{
			if (_TrgEf & PAD_INPUT_6 && _isEffect == 1)
			{
				_isthrow = 1;
			}
			if (_isthrow == 1)
			{
				bombthrow();
			}
			_position_y += _hight;
			if (_position_y <= 0)
			{
				_hight = 0.0f;
				_isEffect = 0;
				_isthrow = 0;
				oldcount = 0;
			}
		}
	}
}

void Lkabomb::Render()
{
	Effekseer_Sync3DSetting();

	DrawEffekseer3D();
	if (_isEffect == 0)
	{
		StopEffekseer3DEffect(_playingEffectHandle);
	}
}

void Lkabomb::bombthrow()
{
	_hight += 1.0f - _throw;
	_throw += 0.5f;
}

#include"sanbomb.h"
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

Sanbomb::Sanbomb()
{
	_effectResourceHandle = LoadEffekseerEffect("res/san_bomb_1.6_2/san_bomb_loop_01.efkefc", 10.0f);
	oldcount = 0;
}

Sanbomb::~Sanbomb()
{
	DeleteEffekseerEffect(_effectResourceHandle);
}

void Sanbomb::Init()
{
}

void Sanbomb::Update(SAN& san)
{
	int keyoldEf = _KeyEf;
	_KeyEf = GetJoypadInputState(DX_INPUT_PAD1);
	_TrgEf = (_KeyEf ^ keyoldEf) & _KeyEf;

	if (_isthrow == 0)
	{
		_position_x = san.vPos.x;
		_position_y = san.vPos.y + 150;
		_position_z = san.vPos.z;
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
	UpdateEffekseer3D();
 


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

void Sanbomb::Render()
{
	Effekseer_Sync3DSetting();

	DrawEffekseer3D();
	if (_isEffect == 0)
	{
		StopEffekseer3DEffect(_playingEffectHandle);
	}
}

void Sanbomb::bombthrow()
{
	_hight += 1.0f - _throw;
	_throw += 0.5f;
}
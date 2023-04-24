/*****************************************************************//**
 * \file   Damage.h
 * \brief  �v���C���[�̃_���[�W����S��
 *
 * \author �y���@���T
 * \date   January 2023
 *********************************************************************/
#pragma once
#include "SANclass.h"
#include "LKAclass.h"
#include "Slime.h"

class SAN;
class LKA;
class ModeGame;
class SanBomb;
class LkaBomb;

class Damage {
	
public:
	Damage();
	~Damage();

	virtual void SwampColl(std::vector<std::unique_ptr<BossSwamp>>& swamps);//�{�X���o�������Ƃ̃_���[�W����
	void Initialize(SAN* san, LKA* lka);
	void Terminate();
	void Process();
	void StageDamage(int StageHandle);//�X�e�[�W�ɂ�����Ƃ̃_���[�W����
	void SlimeDamage(std::vector<std::unique_ptr<Slime>>& slimes);//�X���C���Ƃ̃_���[�W����
	void Render();
	void SetBomb(SanBomb* sanbomb, LkaBomb* lkabomb);

	MV1_COLL_RESULT_POLY_DIM HitPolySan;//�X�e�[�W�ƃT���i�PP�j�Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM HitPolyLka;//�X�e�[�W�ƃ��J�i�QP�j�Ƃ̓����蔻��

	float SanCoolTime;//�T�����_���[�W���󂯂����̃N�[���^�C��
	float LkaCoolTime;//���J���_���[�W���󂯂����̃N�[���^�C��

	bool SanHitFlag;//TRUE�Ȃ�T�������J�����J�̃{���ɐG�ꂽ
	bool LkaHitFlag;//TRUE�Ȃ烋�J���T�����T���̃{���ɐG�ꂽ
	bool SanFloorHitFlag;//TRUE�Ȃ�T�����_���[�W���ɐG�ꂽ
	bool LkaFloorHitFlag;//TRUE�Ȃ烋�J���_���[�W���ɐG�ꂽ
	bool SanSlimeHitFlag;//TRUE�Ȃ�T�����X���C���ɐG�ꂽ
	bool LkaSlimeHitFlag;//TRUE�Ȃ烋�J���X���C���ɐG�ꂽ
	bool stageFlag;//true�̎��Ƀ_���[�W���̔��肪ON�ɂȂ�

	float Distance;//�v���C���[���m�̋���

	MV1_COLL_RESULT_POLY_DIM HitPolySanBomb;//�T���i�PP�j�̃{���ƃ��J�i�QP�j�Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM HitPolyLkaBomb;//���J�i�QP�j�̃{���ƃT���i�PP�j�Ƃ̓����蔻��
	//VOICE�p
	int VOICEdamageSAN[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_01.wav"),
	                          LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/San/San_damage_Voice_02.wav") };//�T���i�PP�j�̃_���[�W�{�C�X
	int VOICEdamageLKA[2] = { LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_01.wav"),
							  LoadSoundMem("res/06_Sound/02_Voice/01_In_Game/03_Damage/Lka/Lka_damage_Voice_02.wav") };//���J�i�QP�j�̃_���[�W�{�C�X

protected:
	SAN* San;
	LKA* Lka;
	ModeGame* Game;
	SanBomb* Sanbomb;
	LkaBomb* Lkabomb;
};
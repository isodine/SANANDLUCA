/*****************************************************************//**
 * \file   Gimmick.h
 * \brief  �V���̓���S��
 *
 * \author �y���@���T
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
#include "SANclass.h"
#include "LKAclass.h"
#include <string>

class SAN;
class LKA;

class Gimmick {
public:
	Gimmick();
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	void SetSanLka(SAN* San, LKA* Lka) {
		san = San;
		lka = Lka;
	}
	void Balance(VECTOR SanPos, VECTOR LkaPos);

	bool GetSanHitFlag() { return SanHitFlag; }
	bool GetLkaHitFlag() { return LkaHitFlag; }
	bool EnumFlag;  //�V���̃X�e�[�^�X���ς�������ǂ���

	int BalanceHandle;//�V���̃��f���̃n���h��
	int AttachAnim1;//�V���̐������[�V����
	int AttachAnimSAN;//�V���̐Ԃ��M�����̌X�����[�V����
	int AttachAnimLKA;//�V���̐��M�����̌X�����[�V����

	VECTOR SANDisk;//�Ԃ��M�̏�̍��W
	VECTOR LKADisk;//���M�̏�̍��W

	float BlendRate;//���[�V�����̃u�����h��
	float BalancePer;//�X���̒l�B�T���̎��|1�ɋ߂Â��A���J�̎��P�ɋ߂Â�

	bool SanHitFlag;//TRUE�Ȃ�Ԃ��M�ɏ����
	bool LkaHitFlag;//TRUE�Ȃ���M�ɏ����
	bool BalanceFlag;//�������ǂ����̃t���O

	
	//SAN�̎��Ԃ��M�̕��ɌX��
	//LKA�̎����M�̕��ɌX��
	//EQUAL�̎����s�A�������͕��s�ɂȂ낤�Ƃ��Ă���
	enum class BALANCE {
		EQUAL,
		SAN,
		LKA,
		NONE
	};

	BALANCE balance;//�V���̃^�C�v
private:
	SAN* san;
	LKA* lka;
};
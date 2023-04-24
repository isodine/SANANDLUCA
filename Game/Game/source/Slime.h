/*****************************************************************//**
 * \file   Slime.h
 * \brief  �X���C���̓���S��
 * 
 * \author �y���@���T
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "AppFrame.h"
#include <string>

class SAN;
class LKA;
class SanBomb;
class LkaBomb;

class Slime {
public:
	void Initialize(float x, float y, float z, int pH);
	void Terminate();
	void Process(VECTOR SanPos, VECTOR LkaPos, int HandleMap, float speed, int mypH);
	void Render(int pH);
	void AcidWalk(float speed);//�_���X���C���̏���
	void AlkaliWalk(float speed);//�A���J�����X���C���̏���
	void SanTargeting(VECTOR SanPos, float speed);//�A���J�����X���C�����T���i�PP�j��ǂ�������
	void LkaTargeting( VECTOR LkaPos, float speed);//�_���X���C�������J�i�QP�j��ǂ�������
	void AcidJump(VECTOR SanPos);//�A���J�����X���C�����T���i�PP�j���U������
	void AlkaliJump(VECTOR LkaPos);//�_���X���C�������J�i�QP�j���U������

	void SetSan(SAN* san);
	void SetLka(LKA* lka);
	void SetSanBomb(SanBomb* sanbomb);
	void SetLkaBomb(LkaBomb* lkabomb);

	float sanDistance;//�X���C���ƃT���̋���
	float lkaDistance;//�X���C���ƃ��J�̋���
	float acidcount;//���[�V�����̃t���[����
	float alkalicount;//���[�V�����̃t���[����
	int slimeHP;//�X���C����HP
	bool slimeAttackFlag;//TRUE�Ȃ�U���ɓ���
	bool sanHitFlag;//TRUE�Ȃ�X���C�����T���ɓ�������
	bool lkaHitFlag;//TRUE�Ȃ烋�J�ɓ�������

	int AttachAnim;
	float TotalTime;
	float PlayTime;

	int slimeHandle;//�X���C���̃��f��
	int acidHandle;//�_���X���C���̃e�N�X�`��
	int alkaliHandle;//�A���J�����X���C���̃e�N�X�`��

	MV1_COLL_RESULT_POLY_DIM SANhitPolyDimAcid;//�_���X���C���Ǝ_���{���Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM LKAhitPolyDimAlkali;//�A���J�����X���C���ƃA���J�����{���Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM LKAhitPolyDimAcid;//�_���X���C���ƃA���J�����{���Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM SANhitPolyDimAlkali;//�A���J�����X���C���Ǝ_���{���Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM hitPolyDim1;//�A���J�����X���C���ƃT���i�PP�j�Ƃ̓����蔻��
	MV1_COLL_RESULT_POLY_DIM hitPolyDim2;//�_���X���C���ƃ��J�i�QP�j�Ƃ̓����蔻��

	MATRIX _rotationMatrix;

	VECTOR slimeDir;//�X���C���̌���
	VECTOR oldPos;//�X���C���̑O�̏ꏊ

	VECTOR sanPos;//�X���C�����猩���T���̌���
	VECTOR lkaPos;//�X���C�����猩�����J�̌���
	VECTOR slimePos;//�X���C���̏ꏊ

	VECTOR acidSlimePos;//�_���X���C���̏ꏊ
	VECTOR alkaliSlimePos;//�A���J�����X���C���̏ꏊ

	VECTOR forward;//�X���C���̐i�ތ���
	VECTOR slimeTargetPos;//�X���C�����ڎw���|�C���g
	VECTOR acidPos[4];//�_���X���C�������񂷂�Ƃ��ɒʉ߂���|�C���g

	VECTOR alkaliPos[4];//�A���J�����X���C�������񂷂�Ƃ��ɒʉ߂���|�C���g

	int SearchPosMinX;//�T�������J�����͈̔͂ɓ�������X���C�����ǂ�������
	int SearchPosMaxX;
	int SearchPosMinZ;
	int SearchPosMaxZ;

	float slimeError;//�X���C���̍��W�̌덷
	int acidPassedCount;//�_���X���C�����ʉ߂�����
	int alkaliPassedCount;//�A���J�����X���C�����ʉ߂�����

	bool acidDieFlag;//TRUE�Ȃ�_���X���C��������
	bool alkaliDieFlag;//TRUE�Ȃ�A���J�����X���C��������

	int mypH = 0;     //�P���_���A�Q���A���J����

	SAN* _san;
	LKA* _lka;
	SanBomb* _sanbomb;
	LkaBomb* _lkabomb;
protected:
	//�X���C���̏��
	enum class STATUS {
		NONE,
		ATTACK,
		HIT,
		WALK_KAI,
		_EOT_
	};
	STATUS _status;

	

};
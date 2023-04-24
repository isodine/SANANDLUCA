/*****************************************************************//**
 * \file   Boss.h
 * \brief  �{�X�̋����S��
 * 
 * \author �y���@���T
 * \date   February 2023
 *********************************************************************/

#pragma once

#include "appframe.h"
#include "BossSwamp.h"
#include "Damage.h"

class ModeBoss;
class SAN;
class LKA;
class SanBomb;
class LkaBomb;

class Boss {
public:
	void Initialize();
	void Terminate();
	void Process(Damage& damage);
	void Render();

	void Targeting(VECTOR sanPos, VECTOR lkaPos);//�U���Ώۂ̌���A���̕����֌���
	void Rush(VECTOR sanPos, VECTOR lkaPos, int SanHandle, int LkaHandle, int MapHandle);//�ːi�U��
	void Capture();//�v���C���[��߂܂��čU������
	void CaptureEnd();//�߂܂��Ă����v���C���[�𗣂�
	void Rotation(VECTOR sanPos, VECTOR lkaPos);//�v���C���[�̕��������݂Ɍ���
	void Walk();//�w�肳�ꂽ�ꏊ�ɕ����Ă���
	void Crush();//�ǏՓˎ�����
	void Search();//�ړ�����ꏊ�����߂�
	void Down();//�|���ꂽ���̏���
	void Idle();//�x�e���[�V�����Đ�
	void Pull();//�ǂ��甲����
	void SwampSpawn(bool IsSan);//�ǂɏՓ˂����Ƃ��^�C�v�ɉ��������𐶐�����

	VECTOR BossSetDir;//�{�X�������\��̕���
	VECTOR BossDir;//�{�X�̌���
	VECTOR HandPos;//�{�X�̂͂��݂̍��W
	VECTOR AddPos;//�{�X�̂͂��݂̒��S�Ɉړ������邽�߂̍��W
	VECTOR SphereCenter;//�{�X�̂͂��݂̒��ɂ���L������ǂƂ̓����蔻����Ƃ邽�߂̋��̒��S���W
	VECTOR BossPosition0;//BossPosition0����BossPosition3�̓{�X���ړ�����ꏊ
	VECTOR BossPosition1;
	VECTOR BossPosition2;
	VECTOR BossPosition3;
	int handleBaseSan;//�_���̏��̃n���h��
	int handleBaseLka;//�A���J�����̏��̃n���h��
	VECTOR swampDir;
	VECTOR swampDegreeDir;
	int SwampCnt;//�����o����

	MATRIX rotationMatrix;//�{�X�̌������o���s��
	VECTOR forward;//�{�X�̌���

	//�{�X�̏��
	enum class BOSSTYPE {
		NONE,
		RUSH,
		CAPTURE,
		CAPTUREEND,
		ROTATION,
		WALK,
		CRUSH,
		SEARCH,
		PULL,
		DOWN,
		IDLE,
	};

	BOSSTYPE type;

	//�{�X�̃^�C�v
	enum class PH {
		ACID,
		ALKALI,
		NONE,
	};

	PH phType;//�{�X�̃^�C�v
	PH oldphType;//�{�X�̑O�̃^�C�v
	
	int RotateCount;//��]���鎞��
	int WaitCount;//���ߍU���̃��[�V�����̃J�E���g
	int PullCount;//������܂ł̕b��
	int CrushCount;//�����΂����鎞��
	int IdleCount;//�x�e���鎞��
	int CaptureCount;//�߂܂��Ă��鎞��
	int EndCount;//�߂܂�����̎���
	int DownCount;//���ꂽ���̎���
	int BossHP;//�{�X�̗̑�
	int BossMaxHP;//�{�X�̍ő�̗�
	int HPhandle;//�{�X��HP�̉摜�̃n���h��
	int iconhandle;//�{�X�̃A�C�R���̃n���h��
	int BGhandle;//�{�X��HP�T�x�[�X�̃n���h��
	int flamehandle;//�{�XHP�t���[���̃n���h��

	int BossSuck;	//�{�X�z����SE
	int BossSearch; //�{�X�T�m��SE
	bool BossSuckflag = false;//�{�X�̋z���T�E���h���Đ����邽�߂Ɉ�x����TRUE�ɂȂ�t���O
	bool BossSearchflag = false;//�{�X�̒T�m�T�E���h���Đ����邽�߂Ɉ�x����TRUE�ɂȂ�t���O

	float StopDir;//��]���~�܂�덷
	float StopPos;//�~�܂�ꏊ�̌덷
	float rotate;//��]���鑬�x

	bool rotateFlag;//TRUE�Ȃ��]����
	bool walkFlag;//TRUE�Ȃ����
	bool rushFlag;//TRUE�Ȃ�U����������U���Ɉڂ�
	bool targetFlag;//TRUE�Ȃ�U���̃^�[�Q�b�g�����߂�
	bool target;//TRUE�Ȃ�T���ɍU��
	bool idleFlag;//TRUE�Ȃ�A�C�h�����[�V����
	bool SanCatchFlag;//TRUE�Ȃ�T����߂܂���
	bool LkaCatchFlag;//TRUE�Ȃ烋�J��߂܂���
	bool crushFlag;//TRUE�Ȃ�TYPE��Crash�ɂ���
	bool AttackedFlag;//TRUE�Ȃ�U�����ꂽ
	bool searchFlag;//TRUE�Ȃ��ʒu�����߂�
	bool downFlag;//TRUE�Ȃ���ꂽ
	bool sanhitEf;//TRUE�Ȃ�_���[�W�G�t�F�N�g�o��
	bool lkahitEf;//TRUE�Ȃ�_���[�W�G�t�F�N�g�o��
	bool bosshitEf;//TRUE�Ȃ�_���[�W�G�t�F�N�g�o��
	bool bossdownEf;//TRUE�Ȃ�_�E���G�t�F�N�g�o��

	int acidHandle;//�_���̂Ƃ��̃e�N�X�`��
	int alkaliHandle;//�A���J�����̂Ƃ��̃e�N�X�`��
	int noneHandle;//�����̎��̃e�N�X�`��

	int Key1P;
	int Trg1P;
	int key;
	int trg;

	SAN* san;
	LKA* lka;
	SanBomb* sanB;
	LkaBomb* lkaB;
	ModeBoss* modeboss;
	modelInf model;
	modelManager* manager;
	BossSwamp Bswamp;
	std::vector<std::unique_ptr<BossSwamp>> swamps;
};
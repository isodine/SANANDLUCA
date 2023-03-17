#pragma once
#include "AppFrame.h"
#include <string>

class SAN;
class LKA;

class Slime {
public:
	void Initialize(float x, float y, float z, int pH);
	void Terminate();
	void Process(VECTOR SanPos, VECTOR LkaPos, int HandleMap, float speed);
	void Render(VECTOR Pos);
	void Walk(float speed);
	void SanTargeting(VECTOR SanPos, float speed);
	void LkaTargeting( VECTOR LkaPos, float speed);
	void SlimeJump(VECTOR SanPos, VECTOR LkaPos);

	void SetSan(SAN* san);
	void SetLka(LKA* lka);

	float sanDistance;//�X���C���ƃT���̋���
	float lkaDistance;//�X���C���ƃ��J�̋���
	float acidcount;//���[�V�����̃t���[����
	float alkalicount;//���[�V�����̃t���[����
	bool slimeAttackFlag;//TRUE�Ȃ�U���ɓ���
	bool sanHitFlag;//TRUE�Ȃ�X���C�����T���ɓ�������
	bool lkaHitFlag;//TRUE�Ȃ烋�J�ɓ�������

	int AttachAnim;
	float TotalTime;
	float PlayTime;

	int slimeHandle;//�X���C���̃��f��
	int acidHandle;//�_���X���C���̃e�N�X�`��
	int alkaliHandle;//�A���J�����X���C���̃e�N�X�`��

	MATRIX _rotationMatrix;

	VECTOR slimeDir;//�X���C���̌���
	VECTOR oldPos;//�X���C���̑O�̏ꏊ

	VECTOR sanPos;//�X���C�����猩���T���̌���
	VECTOR lkaPos;//�X���C�����猩�����J�̌���
	VECTOR slimePos;//�X���C���̏ꏊ

	VECTOR forward;//�X���C���̌���
	VECTOR slimeTargetPos;//�X���C�����ڎw���|�C���g
	VECTOR acidPos[4];
	VECTOR acidPos1;//�_���X���C�������񂷂�Ƃ��ɒʉ߂���|�C���g
	VECTOR acidPos2;
	VECTOR acidPos3;
	VECTOR acidPos4;

	VECTOR alkaliPos[4];
	VECTOR alkaliPos1;//�A���J�����X���C�������񂷂�Ƃ��ɒʉ߂���|�C���g
	VECTOR alkaliPos2;
	VECTOR alkaliPos3;
	VECTOR alkaliPos4;

	int SearchPosMinX;//�T�������J�����͈̔͂ɓ�������X���C�����ǂ�������
	int SearchPosMaxX;
	int SearchPosMinZ;
	int SearchPosMaxZ;

	int mypH = 0;     //�P���_���A�Q���A���J����

	//std::vector<std::unique_ptr<Slime>> slime;
	SAN* _san;
	LKA* _lka;
protected:
	enum class STATUS {
		NONE,
		ATTACK,
		HIT,
		WALK_KAI,
		_EOT_
	};
	STATUS _status;

	

};
/**
 * @file BossSwamp.h
 * @brief �{�X�ɑ�����������ԂŕǂɂԂ���Əo�Ă�����̃v���O����
 * @author �铇����
 * @date March 2023
 */

#pragma once
class BossSwamp
{
public:
	void ModelInitialize();
	void Initialize(bool IsSan,VECTOR Pos,int handleSan, int handleLka);
	void Update(std::vector<std::unique_ptr<BossSwamp>>& swamps);
	void Render();
	void CollCheck(std::vector<std::unique_ptr<BossSwamp>>& swamps);

	// 3D���f���`��p
	int handleBaseSan;			//�����f���P
	int handleBaseLka;			//�����f���P
	int handle;					//���f���f�[�^
	VECTOR vPos;				//�ʒu
	int handleCol;				//���f���̓����蔻��p�ϐ�
	bool isSan = true;			//true�Ȃ�T���Afalse�Ȃ烋�J
	bool neutralization = false;//true�Ȃ璆�a�����Afalse�Ȃ璆�a���ĂȂ�(���a=������)
	float diameter = 90;		//���a�̒���
};

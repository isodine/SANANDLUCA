/**
 * @file IronDoor.h
 * @brief �S�h�A�̃M�~�b�N�𓮂����v���O����
 * @author �铇����
 * @date March 2023
 */

#pragma once
class IronDoor
{
public:
	IronDoor();
	~IronDoor();
	//����������
	void Initialize(bool type, VECTOR Pos);
	//�X�V����
	void Update(SanBomb& sanbomb, LkaBomb& lkabomb);
	//�폜����
	void Terminate();
	//�`�揈��
	void Render();
	//�����蔻�菈��
	void CollCheck(SAN& san, LKA& lka);

	// 3D���f���`��p
	int handle;				//���f���f�[�^
	VECTOR vPos;			//�ʒu
	int handleCol;			//���f���̓����蔻��p�ϐ�
	int handleIronDoor;		//�����f���P
	int handleIronMeltDoor;	//�����f���Q
	bool isSan = false;		//�L�����N�^�[���ʗp
	bool melt = false;		//���f���ω��ʒm
};

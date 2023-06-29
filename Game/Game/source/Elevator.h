/**
 * @file Elevator.h
 * @brief �G���x�[�^�[�̃M�~�b�N�𓮂����v���O����(������)
 * @author �铇����
 * @date February 2023
 */

#pragma once

class Elevator
{
public:
	Elevator();
	~Elevator();
	//����������
	void Initialize();
	//�X�V����
	void Update(Electrode& electr);
	//�폜����
	void Terminate();
	//�`�揈��
	void Render();
	//�ړ�����
	void Move();

	// 3D���f���`��p
	int handle;								//���f���f�[�^
	int handleCol;							//���f���̓����蔻��p�ϐ�
	VECTOR vPos;							//�ʒu
	VECTOR vPosfirst;						//�����x�N�g��
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//�����X�s�[�h
	float upRange = 200.f;					//�㏸����l
	float downRange = 0.f;					//���~�����l
	bool floating = false;					//�t���O���̂P
	bool moving = false;					//�t���O���̂Q
};

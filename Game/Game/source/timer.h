#pragma once

//�������Ԑݒ�p�N���X
class Timer
{
public:
	Timer();
	~Timer();
	//����������
	void Initialize(int time10,int time1,int alltime);
	//�X�V����
	void Update();
	//�`�揈��
	void Render();

	int number[10];		//�摜�p�z��
	int count10;		//2����
	int count1;			//1����
	int firstcnt10;		//�����w��2����
	int firstcnt1;		//�����w��1����
	int firstcnt;		//�����w��
	int secondcnt = 0;	//1�b�v�Z�p�ϐ�
	bool timeup;		//���Ԑ؂�ʒm
};

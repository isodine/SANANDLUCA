#pragma once

class Tube
{
public:
	Tube();
	~Tube();
	//����������
	void Initialize(int Type, VECTOR Pos);
	//�X�V����
	void Update(Electrode& electr);
	//�`�揈��
	void Render();
	//��]����
	void Spin();
	void TubeTouch();
	void SetSanLka(SAN* _san, LKA* _lka);

	// 3D���f���`��p
	int handle;								//���f���f�[�^
	int handleCol;							//���f���̓����蔻��p�ϐ�
	VECTOR vPos;							//�ʒu
	VECTOR vDir;							//����
	VECTOR speed = VGet(0.f, 1.0f, 0.f);	//�����X�s�[�h
	float rightRange = 90.f;				//�E��]���E�l
	float leftRange = -90.f;				//����]���E�l
	float frontRange = 0.f;					//���ʊp�x
	bool spining = false;

	//�������Ă������
	enum TubeType
	{
		Neutrality,
		San,
		Lka
	};
	TubeType Type;

	//�������Ă������
	enum DirType
	{
		Front,
		Right,
		Left
	};
	DirType Dir;

	SAN* san;
	LKA* lka;
};

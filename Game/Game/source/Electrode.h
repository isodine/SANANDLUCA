#pragma once
class Electrode
{
public:
	Electrode();
	~Electrode();
	//����������
	void Initialize(VECTOR Pos,bool is_san);
	//�X�V����
	void Update(SanBomb& sanbomb, LkaBomb& lkabomb);
	//�`�揈��
	void Render();

	// 3D���f���`��p
	int handle;				//���f���f�[�^
	VECTOR vPos;			//�ʒu
	int handleCol;			//���f���̓����蔻��p�ϐ�
	int handleSANelectrode;	//�����f���P
	int handleLKAelectrode;	//�����f���Q
	bool isSan = false;     //true�Ȃ�T���Afalse�Ȃ烋�J
	bool change = false;	//���f���ύX�ʒm
};

#pragma once

class Swamp {
public:
	Swamp();
	~Swamp();
	enum class PHTYPE {
		ASID,
		ALUCALI,
		NONE,
	};

	PHTYPE PHtype;
	PHTYPE oldPHtype;

	int AsidHandle;//�_���̏�
	int AlucaliHandle;//�A���J�����̏�
};
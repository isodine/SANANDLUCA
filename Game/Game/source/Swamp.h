#pragma once

class Swamp {
public:
	Swamp();
	~Swamp();
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	enum class PHTYPE {
		ASID,
		ALUCALI,
		NONE,
	};

	PHTYPE PHtype;
	PHTYPE oldPHtype;

	int AsidHandle;//_«‚ÌÀ
	int AlucaliHandle;//ƒAƒ‹ƒJƒŠ«‚ÌÀ
};
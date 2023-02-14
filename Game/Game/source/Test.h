#pragma once
#include "AppFrame.h"
#include "SANclass.h"
#include "LKAclass.h"
#include <string>

class Test {
public:
	Test();
	~Test();

	void Process();
	void Render();

	int BalanceHandle;

	float BlendRate;

	int AttachAnim1;
	int AttachAnimSAN;
	int AttachAnimLKA;


protected:
	enum class TEST {
		EQUAL,
		SAN,
		LKA,
		NONE
	};

	TEST test;
};
#pragma once

class Gimmick {
public:
	Gimmick();
	void Initialize();
	void Terminate();
	void Process();
	void Render();

	int BalanceHandle;
};
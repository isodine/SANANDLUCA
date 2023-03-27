#pragma once

extern bool timeup;
class Timer
{
public:
	Timer();
	~Timer();
	void Update();            //XV
	void Render();            //•`‰æ

	int number[10];
	int count10 = 5;
	int count1 = 0;
	int secondcnt = 0;
	bool timeup;
};

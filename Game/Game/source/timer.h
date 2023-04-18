#pragma once

extern bool timeup;
class Timer
{
public:
	Timer();
	~Timer();
	void Initialize(int time10,int time1,int alltime);
	void Update();            //XV
	void Render();            //•`‰æ

	int number[10];
	int count10;
	int count1;
	int firstcnt10;
	int firstcnt1;
	int firstcnt;
	int secondcnt = 0;
	bool timeup;
};

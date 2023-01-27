#include "timer.h"
#include "DxLib.h"

bool timeup = false;

Timer::Timer()
{
	//number[0] = LoadGraph("picture/number/0.png");
	//number[1] = LoadGraph("picture/number/1.png");
	//number[2] = LoadGraph("picture/number/2.png");
	//number[3] = LoadGraph("picture/number/3.png");
	//number[4] = LoadGraph("picture/number/4.png");
	//number[5] = LoadGraph("picture/number/5.png");
	//number[6] = LoadGraph("picture/number/6.png");
	//number[7] = LoadGraph("picture/number/7.png");
	//number[8] = LoadGraph("picture/number/8.png");
	//number[9] = LoadGraph("picture/number/9.png");

}

Timer::~Timer()
{
}

void Timer::Update()
{    //XV

	if (secondcnt >= 30) {
		count1--;
		if (count1 == -1 && count10 == 0) {
			count10 = 6;
			count1 = 0;
			timeup = true;
		}
		if (count1 <= -1) {
			count10--;
			count1 = 9;
		}
		secondcnt = 0;
	}
	secondcnt++;
}

void Timer::Render()
{    //•`‰æ

	//if ((count10 <= -1) == false) { DrawExtendGraph(848, 0, 978, 130, number[count10], TRUE);}
	//if ((count1  <= -1) == false) {	DrawExtendGraph(948, 0, 1078, 130, number[count1], TRUE);}
	DrawFormatString(640, 0, GetColor(255, 255, 255), "%d", count10);
	DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", count1);
}
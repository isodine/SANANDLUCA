/**
 * @file timer.cpp
 * @brief 制限時間等で使うタイマー
 * @author 磯島武尊
 * @date July 2022
 */

#include "timer.h"
#include "DxLib.h"

Timer::Timer()
{
	number[0] = LoadGraph("res/01_Count/number_0.png");
	number[1] = LoadGraph("res/01_Count/number_1.png");
	number[2] = LoadGraph("res/01_Count/number_2.png");
	number[3] = LoadGraph("res/01_Count/number_3.png");
	number[4] = LoadGraph("res/01_Count/number_4.png");
	number[5] = LoadGraph("res/01_Count/number_5.png");
	number[6] = LoadGraph("res/01_Count/number_6.png");
	number[7] = LoadGraph("res/01_Count/number_7.png");
	number[8] = LoadGraph("res/01_Count/number_8.png");
	number[9] = LoadGraph("res/01_Count/number_9.png");
	timeup = false;
}

Timer::~Timer()
{
}

void Timer::Initialize(int time10, int time1, int alltime)
{
	firstcnt10 = time10;
	firstcnt1 = time1;
	firstcnt = alltime;
	count10 = firstcnt10;
	count1 = firstcnt1;
}

void Timer::Update()
{    //更新

	if (secondcnt >= firstcnt) {
		count1--;
		if (count1 == -1 && count10 == 0) {
			count10 = firstcnt10;
			count1 = firstcnt1;
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
{    //描画

	if ((count10 <= -1) == false) { DrawExtendGraph(848, 0, 978, 130, number[count10], TRUE);}
	if ((count1  <= -1) == false) {	DrawExtendGraph(948, 0, 1078, 130, number[count1], TRUE);}
	//デバッグ
	//DrawFormatString(640, 0, GetColor(255, 255, 255), "%d", count10);
	//DrawFormatString(650, 0, GetColor(255, 255, 255), "%d", count1);
}
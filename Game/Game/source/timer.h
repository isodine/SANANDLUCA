#pragma once

//制限時間設定用クラス
class Timer
{
public:
	Timer();
	~Timer();
	//初期化処理
	void Initialize(int time10,int time1,int alltime);
	//更新処理
	void Update();
	//描画処理
	void Render();

	int number[10];		//画像用配列
	int count10;		//2桁目
	int count1;			//1桁目
	int firstcnt10;		//初期指定2桁目
	int firstcnt1;		//初期指定1桁目
	int firstcnt;		//初期指定
	int secondcnt = 0;	//1秒計算用変数
	bool timeup;		//時間切れ通知
};

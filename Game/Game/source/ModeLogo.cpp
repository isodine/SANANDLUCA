#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeLogo.h"
#include "ModeTitle.h"

bool ModeLogo::Initialize() {
	if (!base::Initialize()) { return false; }
	logohandle = LoadGraph("res/00_logo/01_AMG-LOGO.png");
	teamlogohandle = LoadGraph("res/00_logo/02_Game_Logo.png");
	return true;
}

bool ModeLogo::Terminate() {
	base::Terminate();

	return true;
}

bool ModeLogo::Process() {
	base::Process();


	return true;
}

bool ModeLogo::Render() {
	//DrawString(0, 0, "チームロゴ", GetColor(255, 255, 255));
  int logo = 0;
  int teamlogo = 0;

  SetDrawScreen(DX_SCREEN_BACK);        // 描画先を裏画面に設定

  while (1) {
    ClearDrawScreen();                   // 裏画面のデータを全て削除

    if (logo >= 0 && logo < 256)                    //cが0~256の時
      SetDrawBright(logo, logo, logo);        //段々あかるく(c= 0->255)
    if (logo >= 256 && logo < 400)                  //cが256~400の時
      SetDrawBright(255, 255, 255);  //通常の明るさ
    if (logo >= 400 && logo < 400 + 256)              //cが400~400+256の時
      SetDrawBright(255 - (logo - 400), 255 - (logo - 400), 255 - (logo - 400));//段々暗く(c= 255->0)

    DrawGraph(335, 480, logohandle, true);  //描画

    logo++;                                  //cをカウントアップ

    if (logo == 400 + 256) 
    {
      break;
    }                 //暗くなり終わったら終了
    ScreenFlip();                                       // 裏画面データを表画面へ反映
  }

  while (1) {
    ClearDrawScreen();                   // 裏画面のデータを全て削除

    if (teamlogo >= 0 && teamlogo < 256)                    //cが0~256の時
      SetDrawBright(teamlogo, teamlogo, teamlogo);        //段々あかるく(c= 0->255)
    if (teamlogo >= 256 && teamlogo < 400)                  //cが256~400の時
      SetDrawBright(255, 255, 255);  //通常の明るさ
    if (teamlogo >= 400 && teamlogo < 400 + 256)              //cが400~400+256の時
      SetDrawBright(255 - (teamlogo - 400), 255 - (teamlogo - 400), 255 - (teamlogo - 400));//段々暗く(c= 255->0)

    DrawGraph(0, 0, teamlogohandle, true);  //描画

    teamlogo++;                                  //cをカウントアップ

    if (teamlogo == 400 + 256)
    {
      break;
    }                 //暗くなり終わったら終了
    if (ProcessMessage() == -1) break;                 //エラーが起きたら終了
    ScreenFlip();                                       // 裏画面データを表画面へ反映
  }
  SetDrawBright(255, 255, 255);  //通常の明るさ
  ChangeMode();
	return true;
}

void ModeLogo::ChangeMode()
{
   ModeServer::GetInstance()->Del(this);
   ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
}
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
	//DrawString(0, 0, "�`�[�����S", GetColor(255, 255, 255));
  int logo = 0;
  int teamlogo = 0;

  SetDrawScreen(DX_SCREEN_BACK);        // �`���𗠉�ʂɐݒ�

  while (1) {
    ClearDrawScreen();                   // ����ʂ̃f�[�^��S�č폜

    if (logo >= 0 && logo < 256)                    //c��0~256�̎�
      SetDrawBright(logo, logo, logo);        //�i�X�����邭(c= 0->255)
    if (logo >= 256 && logo < 400)                  //c��256~400�̎�
      SetDrawBright(255, 255, 255);  //�ʏ�̖��邳
    if (logo >= 400 && logo < 400 + 256)              //c��400~400+256�̎�
      SetDrawBright(255 - (logo - 400), 255 - (logo - 400), 255 - (logo - 400));//�i�X�Â�(c= 255->0)

    DrawGraph(335, 480, logohandle, true);  //�`��

    logo++;                                  //c���J�E���g�A�b�v

    if (logo == 400 + 256) 
    {
      break;
    }                 //�Â��Ȃ�I�������I��
    ScreenFlip();                                       // ����ʃf�[�^��\��ʂ֔��f
  }

  while (1) {
    ClearDrawScreen();                   // ����ʂ̃f�[�^��S�č폜

    if (teamlogo >= 0 && teamlogo < 256)                    //c��0~256�̎�
      SetDrawBright(teamlogo, teamlogo, teamlogo);        //�i�X�����邭(c= 0->255)
    if (teamlogo >= 256 && teamlogo < 400)                  //c��256~400�̎�
      SetDrawBright(255, 255, 255);  //�ʏ�̖��邳
    if (teamlogo >= 400 && teamlogo < 400 + 256)              //c��400~400+256�̎�
      SetDrawBright(255 - (teamlogo - 400), 255 - (teamlogo - 400), 255 - (teamlogo - 400));//�i�X�Â�(c= 255->0)

    DrawGraph(0, 0, teamlogohandle, true);  //�`��

    teamlogo++;                                  //c���J�E���g�A�b�v

    if (teamlogo == 400 + 256)
    {
      break;
    }                 //�Â��Ȃ�I�������I��
    if (ProcessMessage() == -1) break;                 //�G���[���N������I��
    ScreenFlip();                                       // ����ʃf�[�^��\��ʂ֔��f
  }
  SetDrawBright(255, 255, 255);  //�ʏ�̖��邳
  ChangeMode();
	return true;
}

void ModeLogo::ChangeMode()
{
   ModeServer::GetInstance()->Del(this);
   ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
}
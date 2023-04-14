#include "AppFrame.h"
#include "ModeRule.h"
#include "ModeTitle.h"

bool ModeRule::Initialize() {
  if (!base::Initialize()) { return false; }
  Rulehandle[0] = LoadGraph("res/02_Rule/01_rule.png");
  Rulehandle[1] = LoadGraph("res/02_Rule/02_rule.png");
  Rulehandle[2] = LoadGraph("res/02_Rule/03_rule.png");
  Rulehandle[3] = LoadGraph("res/02_Rule/04_rule.png");
  Rulehandle[4] = LoadGraph("res/02_Rule/05_rule.png");
  pushbutton = 0;
  return true;
}

bool ModeRule::Terminate() {
  base::Terminate();
  DeleteGraph(Rulehandle[0]);
  DeleteGraph(Rulehandle[1]);
  DeleteGraph(Rulehandle[2]);
  DeleteGraph(Rulehandle[3]);
  DeleteGraph(Rulehandle[4]);
  return true;
}

bool ModeRule::Process() {
  base::Process();

  int Trg;
  int keyold = Key;
  Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
  Trg = (Key ^ keyold) & Key;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

  if (Trg & PAD_INPUT_1){pushbutton--;}
  if (Trg & PAD_INPUT_2) { pushbutton++; }
  if (pushbutton > 6){pushbutton = 5;}
  if (pushbutton < 0) { pushbutton = 0; }
  if (Trg & PAD_INPUT_2 && pushbutton == 5)
  {
    Terminate();
    ModeServer::GetInstance()->Del(this);
    ModeServer::GetInstance()->Add(new ModeStage0(), 1, "stage00");
    //ModeServer::GetInstance()->Add(new ModeGame(), 1, "stage01");
    //ModeServer::GetInstance()->Add(new ModeBoss(), 1, "boss");
    //ModeServer::GetInstance()->Add(new ModeGame(), 1, "stage01");
  }
  return true;
}

bool ModeRule::Render() {
  DrawGraph(0, 0, Rulehandle[pushbutton], true);
  return true;
}
#include "Gimmick.h"
#include "AppFrame.h"

Gimmick::Gimmick() {
	BalanceHandle = MV1LoadModel("res/Balance_MOmarge.mv1");
}

void Gimmick::Initialize() 
{
	
}

void Gimmick::Terminate() {

}

void Gimmick::Process() {

}
	
void Gimmick::Render() {
	
	MV1SetPosition(BalanceHandle, VGet(-80.0f, 200.0f, 210.0f));
	MV1DrawModel(BalanceHandle);
}

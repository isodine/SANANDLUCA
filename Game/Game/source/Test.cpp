#include "Test.h"

Test::Test() {
	BalanceHandle = MV1LoadModel("res/Balance_MOmarge.mv1");
	test = TEST::EQUAL;
	BlendRate = 0.f;
}

void Test::Process() {
	test = TEST::SAN;

	AttachAnim1 = MV1AttachAnim(BalanceHandle, 0, -1, FALSE);//水平モーションをアタッチする
	AttachAnimSAN = MV1AttachAnim(BalanceHandle, 1, -1, FALSE);//左傾きモーションをアタッチする

	MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnim1, 1.0f - BlendRate);
	MV1SetAttachAnimBlendRate(BalanceHandle, AttachAnimSAN, BlendRate);
	BlendRate += 0.001f;
	MV1SetAttachAnimTime(BalanceHandle, 0, BlendRate);
	MV1SetAttachAnimTime(BalanceHandle, 1, BlendRate);
}

void Test::Render() {
	MV1DrawModel(BalanceHandle);
}

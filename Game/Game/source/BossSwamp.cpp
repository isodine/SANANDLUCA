//BossSwamp::BossSwamp(){}
//BossSwamp::~BossSwamp() {}

void BossSwamp::Initialize(bool IsSan, VECTOR Pos)
{
	IsSan ? handle = MV1LoadModel("res/07_Stage_map/Boss_Stage/acid.mv1") :
		handle = MV1LoadModel("res/07_Stage_map/Boss_Stage/alkali.mv1");
	vPos = Pos;
	MV1SetPosition(handle, vPos);
	handleCol = 0;
	isSan = IsSan;
}

void BossSwamp::Update(std::vector<std::unique_ptr<BossSwamp>>& swamps)
{
	if (neutralization) { return; }

	for (int i = 0; i < swamps.size(); i++)
	{
		if (swamps[i]->isSan == isSan)
		{
			break;
		}
		if (abs(swamps[i]->vPos.x - vPos.x) < diameter && abs(swamps[i]->vPos.z - vPos.z) < diameter)
		{
			neutralization = true;
			swamps[i]->neutralization = true;
		}
		else{ neutralization = false; }
	}
	for (int i = 0; i < swamps.size(); i++)
	{
		if (swamps[i]->neutralization)
		{
			swamps.erase(swamps.begin() + i);
		}
	}
}

void BossSwamp::Render()
{
	MV1DrawModel(handle);
}

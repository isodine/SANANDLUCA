//BossSwamp::BossSwamp(){}
//BossSwamp::~BossSwamp() {}
void BossSwamp::ModelInitialize()
{
	handleBaseSan = MV1LoadModel("res/07_Stage_map/Boss_Stage/acid.mv1");
	handleBaseLka = MV1LoadModel("res/07_Stage_map/Boss_Stage/alkali.mv1");
}

void BossSwamp::Initialize(bool IsSan, VECTOR Pos, int handleSan, int handleLka)
{
	IsSan ? handle = MV1DuplicateModel(handleSan) :
				handle = MV1DuplicateModel(handleLka);
	vPos = Pos;
	MV1SetPosition(handle, vPos);
	handleCol = 0;
	isSan = IsSan;
	neutralization = false;
}

void BossSwamp::Update(std::vector<std::unique_ptr<BossSwamp>>& swamps)
{
	//if (neutralization) { return; }

	//for (int i = 0; i < swamps.size(); i++)
	//{
	//	if (swamps[i]->isSan == isSan)
	//	{
	//		break;
	//	}
	//	if ((abs(swamps[i]->vPos.x - vPos.x) < diameter) && (abs(swamps[i]->vPos.z - vPos.z) < diameter))
	//	{
	//		neutralization = true;
	//		swamps[i]->neutralization = true;
	//	}
	//	//else{ neutralization = false; }
	//}
}

void BossSwamp::Render()
{
	MV1DrawModel(handle);
}

void BossSwamp::CollCheck(std::vector<std::unique_ptr<BossSwamp>>& swamps)
{
	for (int i = 0; i < swamps.size(); i++)
	{
		if (swamps[i]->isSan == isSan)
		{
			break;
		}
		if ((abs(swamps[i]->vPos.x - vPos.x) < diameter) && (abs(swamps[i]->vPos.z - vPos.z) < diameter))
		{
			neutralization = true;
			swamps[i]->neutralization = true;
		}
		//else{ neutralization = false; }
	}
}
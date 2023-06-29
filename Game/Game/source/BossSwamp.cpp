/**
 * @file BossSwamp.cpp
 * @brief ボスに属性がついた状態で壁にぶつかると出てくる沼のプログラム
 * @author 磯島武尊
 * @date March 2023
 */

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

}

void BossSwamp::Render()
{
	MV1DrawModel(handle);
}

void BossSwamp::CollCheck(std::vector<std::unique_ptr<BossSwamp>>& swamps)
{
	if (vPos.z <= 150 || vPos.z >= 1170 || vPos.x <= -480 || vPos.x >= 600)
	{
		neutralization = true;
		return;
	}
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
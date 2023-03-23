#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"
#include "ModeGameOver.h"

namespace {
	std::vector<std::string> splitme(std::string& input, char delimiter)
	{
		std::istringstream stream(input);
		std::string field;
		std::vector<std::string> result;
		char del = ',';
		while (std::getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}
}


ModeBoss::ModeBoss() : ModeBase()
{

}

bool ModeBoss::Initialize() {
	if (!ModeBase::Initialize()) { return false; }
	GameMode = 3;
	//// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j
	//_handle = MV1LoadModel("res/SDChar/SDChar.mv1");
	//_attach_index = -1;		// �A�j���[�V�����A�^�b�`�͂���Ă��Ȃ�

	//// �Đ����Ԃ̏�����
	//_total_time = 0.f;
	//_play_time = 0.0f;
	//// �ʒu,�����̏�����
	//_vPos = VGet(0, 0, 0);
	//_vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���
	//�J�����ݒ�
		_bossCam._vTarget = VGet(0, 0, 650);
		_bossCam._vPos = VGet(0, 1100, 0);
		_bossCam._clipNear = 2.f;
		_bossCam._clipFar = 20000.f;

		Count = 0;

		boss.modeboss = this;
		boss.san = &san;
		boss.lka = &lka;

		boss.sanB = &sanbomb;
		boss.lkaB = &lkabomb;
	
	// �}�b�v
	_handleMap = MV1LoadModel("res/07_Stage_map/Boss_Stage/Boss_Stage.mv1");
	MV1SetPosition(_handleMap, VGet(50.0f, 0.0f, 700.0f));
	_handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1");

	// �R���W�������̐���
	frameMapCollisionfloor = MV1SearchFrame(_handleMap, "floor1");
	frameMapCollisionwall = MV1SearchFrame(_handleMap, "wall");
	MV1SetupCollInfo(_handleMap, frameMapCollisionfloor, 16, 16, 16);
	MV1SetupCollInfo(_handleMap, frameMapCollisionwall, 16, 16, 16);
	// �R���W�����̃t���[����`�悵�Ȃ��ݒ�
	MV1SetFrameVisible(_handleMap, frameMapCollisionfloor, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	/*MV1SetFrameVisible(_handleMap, 0, FALSE);
	MV1SetFrameVisible(_handleMap, 1, FALSE);*/

	////�}�X�N�̎����^�p
	//MaskHandle = LoadMask("res/San_Lka_Mask.png");
	//CreateMaskScreen();


	//�t�H�O���g���Ă݂�
	//SetFogEnable(TRUE);

	// �t�H�O�̐F��ݒ�
	//SetFogColor(255, 255, 255);

	// �t�H�O�̊J�n�����A�I��������ݒ�
	//SetFogStartEnd(0.0f, 3000.0f);

	// ���̑�������
	_bViewCollision = FALSE;

	sanbomb.Initialize(san);
	lkabomb.Initialize(lka);

	throughtime = 0.0f;
	height = 0.0f;

	boss.Initialize();

	san.SetCamera(&_bossCam);
	san.SetBomb(&sanbomb);
	san.SetDamage(&damage);

	san.Initialize();
	san.floorCol = frameMapCollisionfloor;
	san.wallCol = frameMapCollisionwall;
	san.stageHandle = _handleMap;

	lka.SetCamera(&_bossCam);
	lka.SetBomb(&lkabomb);
	lka.SetDamage(&damage);

	lka.Initialize();
	lka.floorCol = frameMapCollisionfloor;
	lka.wallCol = frameMapCollisionwall;
	lka.stageHandle = _handleMap;

	damage.Initialize(&san, &lka);
	damage.stageFlag = false;
	//enemy.Initialize();
	//CSV�ɂ�鏉�����i���x���f�U�C�����Ɏ����j

	std::ifstream ifs("res/test.csv");

	std::string line;
	std::vector<std::string> strresult;
	std::vector<int> intresult;
	int x, y, z;
	int cnt = 0;
	while (std::getline(ifs, line)) {

		std::vector < std::string > strvec = splitme(line, ',');

		for (int i = 0; i < strvec.size(); i++) {
			int readInteger = atoi(strvec.at(i).c_str());
			if (readInteger != 0 || (strlen(strvec.at(i).c_str()) == 1 && strvec.at(i).c_str()[0] == '0'))
			{
				std::cout << readInteger << "\n";
				intresult.push_back(readInteger);
				if (i == 1)
				{
					x = readInteger;
				}
				if (i == 2)
				{
					y = readInteger;
				}
				if (i == 3)
				{
					z = readInteger;
					if (cnt == 1)
					{
						san.vPos = VGet(x, y, z);
					}
					else if (cnt == 2)
					{
						lka.vPos = VGet(x, y, z);
					}
				}
			}
			else
			{
				std::cout << strvec.at(i) << "\n";
				strresult.push_back(strvec.at(i));
			}
		}
		cnt++;
	}

	PlayMusic("res/06_Sound/01_BGM/Confectioner.mp3", DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeBoss::Terminate() {
	ModeBase::Terminate();
	return true;
}

bool ModeBoss::Process() {
	ModeBase::Process();
	Count += 1;
	//for (auto&& SanLka : sanlka) {
	//	SanLka->Update();
	//}-
	/*san.SetOnBalance(gimmick.GetSanHitFlag());
	lka.SetOnBalance(gimmick.GetLkaHitFlag());*/
	san.Update(damage);
	lka.Update(damage);
	damage.Process();
	boss.Process();
	sanbomb.Update(san);
	lkabomb.Update(lka);
	sancircle.Update(san,lka);
	lkacircle.Update(san,lka);
	bossrun.Update(boss);
	bossattack.Update(boss, damage);
	bossdamage.Update(boss);
	bossdown.Update(boss);

	//��
	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg = (Key ^ keyold) & Key;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	int checkKey = PAD_INPUT_2;

	if (boss.downFlag == true) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeEnding(), 1, "ending");
	}

	if ((san.vPos.y <= -1000.0f) || (lka.vPos.y <= -1000.0f) || (san.HP <= 0) || (lka.HP <= 0))
	{
		StopMusic();
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "gameover");
	}
	if (boss.downFlag) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeEnding(), 1, "ending");
	}

	return true;
}

bool ModeBoss::Render() {
	ModeBase::Render();

	// 3D��{�ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// ���C�g�ݒ�
	SetUseLighting(TRUE);
#if 1	// ���s���C�g
	SetGlobalAmbientLight(GetColorF(0.1f, 0.1f, 0.1f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 1));

	/*LightHandle = CreateDirLightHandle(VGet(0.0f, 0.0f, 1.0f));
	SetLightAmbColorHandle(LightHandle, GetColorF(0.5f, 0.0f, 0.0f, 0.0f));*/

#endif
#if 0	// �|�C���g���C�g
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_vPos, VGet(0, 50.f, 0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	// �J�����ݒ�X�V
		SetCameraPositionAndTarget_UpVecY(_bossCam._vPos, _bossCam._vTarget);
		SetCameraNearFar(_bossCam._clipNear, _bossCam._clipFar);
	

	// 0,0,0�𒆐S�ɐ�������
	{
		//float linelength = 1000.f;
		//VECTOR v = { 0, 0, 0 };
		//DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		//DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// �J�����^�[�Q�b�g�𒆐S�ɒZ����������
	{
		float linelength = 10.f;
		VECTOR v = _cam._vTarget;
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// �Đ����Ԃ��Z�b�g����
	//MV1SetAttachAnimTime(_handle, _attach_index, _play_time);

	{
		// �R���W��������p���C���̕`��
		//if (_bViewCollision) {
		//	DrawLine3D(VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));
		//}
	}
	// �}�b�v���f����`�悷��
	{
		MV1SetScale(_handleSkySphere, VGet(2.0f, 2.0f, 2.0f));
		MV1DrawModel(_handleSkySphere);

		MV1DrawModel(_handleMap);
		//DrawMask(0, 0, MaskHandle, DX_MASKTRANS_BLACK);
	}
	boss.Render();
	san.Render(damage);
	lka.Render(damage);
	//DrawFormatString(0, 30, GetColor(255, 0, 0), "sanPos(%f,%f,%f)", san.vPos.x, san.vPos.y, san.vPos.z);
	// �f�o�b�O�\��
	{
		//DrawSphere3D(boss.BossPosition0, 200, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
		//DrawSphere3D(boss.BossPosition1, 200, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
		//DrawSphere3D(boss.BossPosition2, 200, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
		//DrawSphere3D(boss.BossPosition3, 200, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), false);
		/*int x = 0, y = 0, size = 16;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam._vTarget.x, _cam._vTarget.y, _cam._vTarget.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _cam._vPos.x, _cam._vPos.y, _cam._vPos.z); y += size;
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float length = sqrt(sz * sz + sx * sx);
		float rad = atan2(sz, sx);
		float deg = RAD2DEG(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  San pos    = (%5.2f, %5.2f, %5.2f)", san.vPos.x, san.vPos.y, san.vPos.z); y += size;
		switch (san._status)
		{
		case Player::STATUS::WAIT:
			DrawFormatString(x, y, GetColor(255, 0, 0), "  San states = WAIT"); y += size;
			break;
		case Player::STATUS::WALK:
			DrawFormatString(x, y, GetColor(255, 0, 0), "  San states = WALK"); y += size;
			break;
		case Player::STATUS::JUMP:
			DrawFormatString(x, y, GetColor(255, 0, 0), "  San states = JUMP"); y += size;
			break;
		}
		DrawFormatString(x, y, GetColor(255, 0, 0), "  Lka pos    = (%5.2f, %5.2f, %5.2f)", lka.vPos.x, lka.vPos.y, lka.vPos.z); y += size;
		switch (lka._status)
		{
		case Player::STATUS::WAIT:
			DrawFormatString(x, y, GetColor(255, 0, 0), "  Lka states = WAIT"); y += size;
			break;
		case Player::STATUS::WALK:
			DrawFormatString(x, y, GetColor(255, 0, 0), "  Lka states = WALK"); y += size;
			break;
		case Player::STATUS::JUMP:
			DrawFormatString(x, y, GetColor(255, 0, 0), "  Lka states = JUMP"); y += size;
			break;
		}*/
	}
	sanbomb.Render();
	lkabomb.Render();
	sancircle.Render();
	lkacircle.Render();
	bossrun.Render();
	bossattack.Render(boss);
	bossdamage.Render(boss);
	bossdown.Render();
	return true;
}


#include "AppFrame.h"
//#include "ApplicationMain.h"
//#include "ModeGame.h"
#include "ModeGameOver.h"

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

ModeGame::ModeGame() : ModeBase()
{
	// �}�b�v
	_handleMap = MV1LoadModel("res/07_Stage_map/01_Stage/Stage_01.fbm/Stage_01.mv1");
	MV1SetPosition(_handleMap, VGet(50.0f, 0.0f, 700.0f));
	_handleSkySphere = MV1LoadModel("res/SkySphia/sky.mv1");

	// �R���W�������̐���
	frameMapCollisionfloor = 0;  /*MV1SearchFrame(_handleMap, "Con_bot_pPlane6");*/
	frameMapCollisionwall = 1;  /*MV1SearchFrame(_handleMap, "Con_tate_pPlane3");*/
	frameMapCollisiongoalSAN = 4;
	frameMapCollisiongoalLKA = 5;
	MV1SetupCollInfo(_handleMap, frameMapCollisionfloor, 16, 16, 16);
	MV1SetupCollInfo(_handleMap, frameMapCollisionwall, 16, 16, 16);

	// �R���W�����̃t���[����`�悵�Ȃ��ݒ�
	MV1SetFrameVisible(_handleMap, frameMapCollisionfloor, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	MV1SetFrameVisible(_handleMap, 2, FALSE);
	MV1SetFrameVisible(_handleMap, 3, FALSE);

	////�}�X�N�̎����^�p
	//MaskHandle = LoadMask("res/San_Lka_Mask.png");
	//CreateMaskScreen();

	// �J�����̐ݒ�i�킩��₷���ʒu�Ɂj
	_cam._vPos = VGet(0, 700.f, -900.f);
	_cam._vTarget = VGet(0, 60, 0);
	_cam._clipNear = 2.f;
	_cam._clipFar = 20000.f;

	//�V���h�E�}�b�v�p�ϐ������̏�����
	ShadowMapUpVec = VGet(-500.f, -1000.f, -1000.f);     //�T�����z��
	ShadowMapDownVec = VGet(500.f, 1000.f, 1000.f);      //���J���z��

	//�t�H�O���g���Ă݂�
	//SetFogEnable(TRUE);

	// �t�H�O�̐F��ݒ�
	//SetFogColor(255, 255, 255);

	// �t�H�O�̊J�n�����A�I��������ݒ�
	//SetFogStartEnd(0.0f, 3000.0f);

	// ���̑�������
	_bViewCollision = FALSE;

	throughtime = 0.0f;
	height = 0.0f;
}

bool ModeGame::Initialize() {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	if (!base::Initialize()) { return false; }


	// �}�b�v
	_handleMap = MV1LoadModel("res/07_Stage_map/01_Stage/Stage_01.fbm/Stage_01.mv1");
	MV1SetPosition(_handleMap, VGet(50.0f, 0.0f, 700.0f));
	_handleSkySphere = MV1LoadModel("res/SkySphia/sky.mv1");

	// �R���W�������̐���
	frameMapCollisionfloor = 0;  /*MV1SearchFrame(_handleMap, "Con_bot_pPlane6");*/
	frameMapCollisionwall = 1;  /*MV1SearchFrame(_handleMap, "Con_tate_pPlane3");*/
	frameMapCollisiongoalSAN = 4;
	frameMapCollisiongoalLKA = 5;
	MV1SetupCollInfo(_handleMap, frameMapCollisionfloor, 16, 16, 16);
	MV1SetupCollInfo(_handleMap, frameMapCollisionwall, 16, 16, 16);

	// �R���W�����̃t���[����`�悵�Ȃ��ݒ�
	MV1SetFrameVisible(_handleMap, frameMapCollisionfloor, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	MV1SetFrameVisible(_handleMap, 2, FALSE);
	MV1SetFrameVisible(_handleMap, 3, FALSE);
	//�Q�[���I�[�o�[�}�X�N
	Grhandle[0] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_01.png");
	Grhandle[1] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_02.png");
	Grhandle[2] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_03.png");
	Grhandle[3] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_04.png");
	Grhandle[4] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_05.png");
	Grhandle[5] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_06.png");
	Grhandle[6] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_07.png");
	Grhandle[7] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_08.png");
	Grhandle[8] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_09.png");
	Grhandle[9] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_10.png");
	Grhandle[10] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_11.png");
	Grhandle[11] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_12.png");
	Grhandle[12] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_13.png");
	Grhandle[13] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_14.png");
	Grhandle[14] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_15.png");
	Grhandle[15] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_16.png");
	Grhandle[16] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_17.png");
	Grhandle[17] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_18.png");
	Grhandle[18] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_19.png");
	Grhandle[19] = LoadGraph("res/Gameover_pattern_01/Gameover_pattern_01_20.png");

	Isgameover = false;
	gameoverchange = false;
	Isgamestart = true;
	gameovercount = 0;
	gamestartcount = 19;
	////�}�X�N�̎����^�p
	//MaskHandle = LoadMask("res/San_Lka_Mask.png");
	//CreateMaskScreen();

	// �J�����̐ݒ�i�킩��₷���ʒu�Ɂj
	_cam._vPos = VGet(0, 700.f, -900.f);
	_cam._vTarget = VGet(0, 60, 0);
	_cam._clipNear = 2.f;
	_cam._clipFar = 20000.f;

	//�V���h�E�}�b�v�p�ϐ������̏�����
	ShadowMapUpVec = VGet(-500.f, -1000.f, -1000.f);     //�T�����z��
	ShadowMapDownVec = VGet(500.f, 1000.f, 1000.f);      //���J���z��

	//�t�H�O���g���Ă݂�
	//SetFogEnable(TRUE);

	// �t�H�O�̐F��ݒ�
	//SetFogColor(255, 255, 255);

	// �t�H�O�̊J�n�����A�I��������ݒ�
	//SetFogStartEnd(0.0f, 3000.0f);

	// ���̑�������
	_bViewCollision = FALSE;

	throughtime = 0.0f;
	height = 0.0f;

	//irondoor.Initialize();
	//electrode.Initialize(VGet(200.f, 70.f, 1000.f), true);
	//elevator.Initialize();
	//MV1SetupCollInfo(elevator.handle, elevator.handleCol, 4, 4, 4);

	//auto Tube1 = std::make_unique<Tube>();
	//Tube1->Initialize(0, VGet(0.f, 70.f, 1000.f));
	//tubes.emplace_back(std::move(Tube1));

	//auto Tube2 = std::make_unique<Tube>();
	//Tube2->Initialize(1, VGet(0.f, 70.f, 800.f));
	//tubes.emplace_back(std::move(Tube2));

	//auto Tube3 = std::make_unique<Tube>();
	//Tube3->Initialize(2, VGet(0.f, 70.f, 600.f));
	//tubes.emplace_back(std::move(Tube3));

	//damage.SetGame(this);

	san.SetCamera(&_cam);
	san.SetBomb(&sanbomb);
	san.SetDamage(&damage);
	san.SetGimmick(&gimmick);

	san.Initialize();
	sanbomb.EffectReset();
	san.floorCol = frameMapCollisionfloor;
	san.wallCol = frameMapCollisionwall;
	san.goalColSAN = frameMapCollisiongoalSAN;
	san.ironDoorHandle = irondoor.handle;
	san.ironDoorCol = irondoor.handleCol;
	san.elevatorHnadle = elevator.handle;
	san.elevatorCol = elevator.handleCol;
	san.stageHandle = _handleMap;

	lka.SetCamera(&_cam);
	lka.SetBomb(&lkabomb);
	lka.SetDamage(&damage);
	lka.SetGimmick(&gimmick);

	lka.Initialize();
	lka.floorCol = frameMapCollisionfloor;
	lka.wallCol = frameMapCollisionwall;
	lka.goalColLKA = frameMapCollisiongoalLKA;
	lka.ironDoorHandle = irondoor.handle;
	lka.ironDoorCol = irondoor.handleCol;
	lka.elevatorHnadle = elevator.handle;
	lka.elevatorCol = elevator.handleCol;
	lka.stageHandle = _handleMap;

	damage.Initialize(&san, &lka);
	//slime.Initialize();
	gimmick.Initialize();
	gimmick.SetSanLka(&san, &lka);
	sanbomb.Initialize(san);
	lkabomb.Initialize(lka);

	//CSV�ɂ�鏉�����i���x���f�U�C�����Ɏ����j

	std::ifstream ifs("res/test.csv");

	std::string line;
	std::vector<std::string> strresult;
	std::vector<int> intresult;
	int x, y, z, pH;
	int cnt = 0;
	while (std::getline(ifs, line)) {

		std::vector < std::string > strvec = splitme(line, ',');

		for (int i = 0; i < strvec.size(); i++) {
			int readInteger = atoi(strvec.at(i).c_str());
			if (readInteger != 0 || (strlen(strvec.at(i).c_str()) == 1 && strvec.at(i).c_str()[0] == '0'))
			{
				std::cout << readInteger << "\n";
				intresult.push_back(readInteger);
				if (i == 1) { x = readInteger; }
				if (i == 2) { y = readInteger; }
				if (i == 3) { z = readInteger; }
				if (i == 4) {
					pH = readInteger;

					if (cnt == 1) { san.vPos = VGet(x, y, z); pH == 1 ? san.SetType(true) : san.SetType(false); }
					else if (cnt == 2) { lka.vPos = VGet(x, y, z); pH == 1 ? lka.SetType(true) : lka.SetType(false); }

					else if (cnt == 3)
					{
						//auto Slime1 = std::make_unique<Slime>();
						//Slime1->Initialize(x, y, z, pH);
						//slimes.emplace_back(std::move(Slime1));
					}
					else if (cnt == 4)
					{
						//auto Slime2 = std::make_unique<Slime>();
						//Slime2->Initialize(x, y, z, pH);
						//slimes.emplace_back(std::move(Slime2));
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

	//CSV�̒����ɃJ������ǂ�������
	_cam._vPos.x += (san.vPos.x + lka.vPos.x) / 2.f;
	_cam._vPos.y += (san.vPos.y + lka.vPos.y) / 2.f;
	_cam._vPos.z += (san.vPos.z + lka.vPos.z) / 2.f;
	_cam._vTarget.x = ((san.vPos.x + lka.vPos.x) / 2.f);
	_cam._vTarget.y = ((san.vPos.y + lka.vPos.y) / 2.f);
	_cam._vTarget.z = ((san.vPos.z + lka.vPos.z) / 2.f);


	//�V���h�E�}�b�v�̐���
	ShadowMapHandle = MakeShadowMap(1024, 1024);

	SetShadowMapLightDirection(ShadowMapHandle, VGet(0, -1, 0));

	// �V���h�E�}�b�v�ւ̕`��̏���
	ShadowMap_DrawSetup(ShadowMapHandle);

	// �V���h�E�}�b�v�փX�e�[�W���f���̕`��
	//MV1DrawModel(_handleMap);

	// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
	MV1DrawModel(san.Mhandle);
	MV1DrawModel(lka.Mhandle);

	// �V���h�E�}�b�v�ւ̕`����I��
	ShadowMap_DrawEnd();

	PlayMusic("res/06_Sound/01_BGM/Stage/Confectioner.mp3", DX_PLAYTYPE_LOOP);


	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGame::Process() {
	
	base::Process();
	gimmick.Balance(san.vPos, lka.vPos);
	if (!modeStart)
	{
		PlaySoundMem(VOICEstartSANLKA[GetRand(5)], DX_PLAYTYPE_BACK, true);
		modeStart = true;
	}
	MV1RefreshCollInfo(elevator.handle, elevator.handleCol);
	san.SetOnBalance(gimmick.GetSanHitFlag());
	lka.SetOnBalance(gimmick.GetLkaHitFlag());
	gimmick.SanHitFlag = false;
	gimmick.LkaHitFlag = false;
	san.Update(damage);
	lka.Update(damage);
	damage.Process();
	//slime.SlimeU(san.vPos, lka.vPos, _handleMap, 1.0f);
	gimmick.Balance(san.vPos, lka.vPos);

	for (auto&& Slimes : slimes) {
		Slimes->Process(san.vPos, lka.vPos, _handleMap, 2.f);
	}

	if ((san.vPos.y <= -1000.0f) || (lka.vPos.y <= -1000.0f) || (san.HP <= 0) || (lka.HP <= 0)||timer.timeup == true)
	{
		Isgameover = true;
		sanbomb.EffectReset();
		sancircle.EffectReset();
		lkabomb.EffectReset();
		lkacircle.EffectReset();
		//BGM��~
		StopMusic();

		// �V���h�E�}�b�v�̍폜
		DeleteShadowMap(ShadowMapHandle);

		ChangePanSoundMem(255, san.VOICEdeathSAN);
		ChangePanSoundMem(-255, lka.VOICEdeathLKA);
		PlaySoundMem(san.VOICEdeathSAN, DX_PLAYTYPE_BACK, true);
		PlaySoundMem(lka.VOICEdeathLKA, DX_PLAYTYPE_BACK, true);
		if (gameoverchange == true)
		{
			ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "gameover");
		}
	}
	timer.Update();
	sanbomb.Update(san);
	lkabomb.Update(lka);
	sancircle.Update(san, lka);
	lkacircle.Update(san, lka);
	//sanheal.Update(san);
	//lkaheal.Update(lka);
	//if (!(irondoor.melt))
	//{
	//	irondoor.Update(sanbomb);
	//	if (irondoor.melt)
	//	{
	//		san.ironDoorHandle = irondoor.handle;
	//		lka.ironDoorHandle = irondoor.handle;
	//	}
	//}
	//electrode.Update(sanbomb, lkabomb);
	//elevator.Update(electrode);
	//for (auto&& Tubes : tubes) {
	//	Tubes->Update(electrode);
	//}

	//��
	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg = (Key ^ keyold) & Key;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j

	int checkKey = PAD_INPUT_10;
	if (Trg & checkKey || (san.goal && lka.goal)) {
		//BGM��~
		StopMusic();

		// �V���h�E�}�b�v�̍폜
		DeleteShadowMap(ShadowMapHandle);

		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeBoss(), 1, "boss");
	}

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// 3D��{�ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// ���C�g�ݒ�
	SetUseLighting(TRUE);
#if 1	// ���s���C�g
	SetGlobalAmbientLight(GetColorF(0.1f, 0.1f, 0.1f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 1));
	//SetLightEnable(FALSE);
	//SetLightDirection(VSub(_cam._vTarget, _cam._vPos));

	/*LightHandle = CreateDirLightHandle(VGet(0.0f, 0.0f, 1.0f));
	SetLightAmbColorHandle(LightHandle, GetColorF(0.5f, 0.0f, 0.0f, 0.0f));*/

#endif
#if 0	// �|�C���g���C�g
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_vPos, VGet(0, 50.f, 0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	// �J�����ݒ�X�V
	_cam._vTarget = VScale(VAdd(san.vPos, lka.vPos), 0.5);
	_cam._vPos = VAdd(_cam._vTarget, VGet(0, 400.f, -500.f));
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

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
		gimmick.Render();
		for (auto&& Slimes : slimes) {
			Slimes->Render(Slimes->slimePos);
		}
	}
	//�}�b�v���f����`�悷��
	{
		// �V���h�E�}�b�v�ւ̕`��̏���
		ShadowMap_DrawSetup(ShadowMapHandle);

		// �V���h�E�}�b�v�փL�����N�^�[���f���̕`��
		MV1DrawModel(san.Mhandle);
		MV1DrawModel(lka.Mhandle);

		// �V���h�E�}�b�v�ւ̕`����I��
		ShadowMap_DrawEnd();

		SetShadowMapDrawArea(ShadowMapHandle, VAdd(san.vPos, ShadowMapUpVec), VAdd(lka.vPos, ShadowMapDownVec));

		SetUseShadowMap(0, ShadowMapHandle);

		// �X�e�[�W���f���̕`��
		MV1DrawModel(_handleMap);

		// �`��Ɏg�p����V���h�E�}�b�v�̐ݒ������
		SetUseShadowMap(0, -1);

		MV1SetScale(_handleSkySphere, VGet(2.0f, 2.0f, 2.0f));
		MV1DrawModel(_handleSkySphere);

		//MV1DrawModel(_handleMap);
		//DrawMask(0, 0, MaskHandle, DX_MASKTRANS_BLACK);
	}
	// �f�o�b�O�\��
	if (san.debagMode || lka.debagMode)
	{
		int x = 0, y = 0, size = 16;
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
		}
		//DrawCapsule3D(VGet(san.vPos.x, san.vPos.y + 30, san.vPos.z), VGet(san.vPos.x, san.vPos.y + 75, san.vPos.z), 30.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
		//DrawCapsule3D(VGet(lka.vPos.x, lka.vPos.y + 30, lka.vPos.z), VGet(lka.vPos.x, lka.vPos.y + 75, lka.vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
	}
	//DrawFormatString(0, 300, GetColor(255, 0, 0), "SANDisk(%f,%f,%f)", gimmick.SANDisk.x, gimmick.SANDisk.y, gimmick.SANDisk.z);
	//DrawFormatString(0, 220, GetColor(0, 0, 0), "BlendRate = %f", gimmick.BlendRate);
	//DrawFormatString(0, 250, GetColor(0, 0, 0), "hitPolyDimSAN.HitNum = %d", san.hitPolyDimSAN.HitNum);
	//DrawFormatString(0, 300, GetColor(0, 0, 0), "SanHitFlag = %d", gimmick.SanHitFlag);
	lka.Render(damage);
	san.Render(damage);
	sanbomb.Render();
	lkabomb.Render();
	sancircle.Render();
	lkacircle.Render();
	timer.Render();
	//irondoor.Render();
	//electrode.Render();
	//elevator.Render();
	//for (auto&& Tubes : tubes) {
	//	Tubes->Render();
	//}
	if (Isgameover == true)
	{
		DrawGraph(0, 0, Grhandle[gameovercount], true);
		gameovercount++;
		if (gameovercount >= 19)DrawGraph(0, 0, Grhandle[19], true), gameoverchange = true;
	}
	if (Isgamestart == true)
	{
		DrawGraph(0, 0, Grhandle[gamestartcount], true);
		gamestartcount--;
		if (gamestartcount <= 0)DrawGraph(0, 0, Grhandle[0], true), Isgamestart = false;
	}
	return true;
}

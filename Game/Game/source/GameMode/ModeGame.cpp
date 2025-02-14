
#include "AppFrame.h"
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
	// マップ
	_handleMap = MV1LoadModel("res/07_Stage_map/01_Stage/Stage_01.fbm/Stage_01.mv1");
	MV1SetPosition(_handleMap, VGet(50.0f, 0.0f, 700.0f));
	_handleSkySphere = MV1LoadModel("res/SkySphia/sky.mv1");

	// コリジョン情報の生成
	frameMapCollisionfloor = 0;
	frameMapCollisionwall = 1;
	frameMapCollisiongoalSAN = 4;
	frameMapCollisiongoalLKA = 5;
	MV1SetupCollInfo(_handleMap, frameMapCollisionfloor, 16, 16, 16);
	MV1SetupCollInfo(_handleMap, frameMapCollisionwall, 16, 16, 16);

	// コリジョンのフレームを描画しない設定
	MV1SetFrameVisible(_handleMap, frameMapCollisionfloor, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	MV1SetFrameVisible(_handleMap, 2, FALSE);
	MV1SetFrameVisible(_handleMap, 3, FALSE);


	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet(0, 700.f, -900.f);
	_cam._vTarget = VGet(0, 60, 0);
	_cam._clipNear = 2.f;
	_cam._clipFar = 20000.f;

	//シャドウマップ用変数たちの初期化
	ShadowMapUpVec = VGet(-500.f, -1000.f, -1000.f);     //サン側想定
	ShadowMapDownVec = VGet(500.f, 1000.f, 1000.f);      //ルカ側想定


	// その他初期化
	_bViewCollision = FALSE;

	throughtime = 0.0f;
	height = 0.0f;
}

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	// マップ
	_handleMap = MV1LoadModel("res/07_Stage_map/01_Stage/Stage_01.fbm/Stage_01.mv1");
	MV1SetPosition(_handleMap, VGet(50.0f, 0.0f, 700.0f));
	_handleSkySphere = MV1LoadModel("res/07_Stage_map/00_Stage/00SkyCube_B/sky.mv1");
	// コリジョン情報の生成
	frameMapCollisionfloor = 0;
	frameMapCollisionwall = 1;
	frameMapCollisiongoalSAN = 4;
	frameMapCollisiongoalLKA = 5;
	MV1SetupCollInfo(_handleMap, frameMapCollisionfloor, 16, 16, 16);
	MV1SetupCollInfo(_handleMap, frameMapCollisionwall, 16, 16, 16);

	// コリジョンのフレームを描画しない設定
	MV1SetFrameVisible(_handleMap, frameMapCollisionfloor, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	MV1SetFrameVisible(_handleMap, 2, FALSE);
	MV1SetFrameVisible(_handleMap, 3, FALSE);
	MV1SetFrameVisible(_handleMap, 4, FALSE);
	MV1SetFrameVisible(_handleMap, 5, FALSE);

	//ゲームオーバーマスク
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

	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet(0, 700.f, -900.f);
	_cam._vTarget = VGet(0, 60, 0);
	_cam._clipNear = 2.f;
	_cam._clipFar = 20000.f;

	//シャドウマップ用変数たちの初期化
	ShadowMapUpVec = VGet(-500.f, -1000.f, -1000.f);     //サン側想定
	ShadowMapDownVec = VGet(500.f, 1000.f, 1000.f);      //ルカ側想定

	//UVスクロール
	_UVScroll_U = 0.0f;
	_UVScroll_V = 0.0f;

	// その他初期化
	_bViewCollision = FALSE;

	throughtime = 0.0f;
	height = 0.0f;

	respawnstartSan = VGet(-30.f, 20.f, 670.f);
	respawnstartLka = VGet(100.f, 20.f, 670.f);

	respawn1stPosSan = VGet(201.f, 302.f, 2943.f);
	respawn1stPosLka = VGet(-92.f, 302.f, 2943.f);

	respawn2ndPosSan = VGet(-84.f, 529.f, 6296.f);
	respawn2ndPosLka = VGet(153.f, 529.f, 6296.f);


	auto Tube2 = std::make_unique<Tube>();
	Tube2->Initialize(1, VGet(-113.f, 301.f, 3389.f));
	MV1SetupCollInfo(Tube2->handle, tube.handleCol, 4, 4, 4);
	san.tubeCol[1] = Tube2->handleCol;
	lka.tubeCol[1] = Tube2->handleCol;
	san.tubeHandle[1] = Tube2->handle;
	lka.tubeHandle[1] = Tube2->handle;
	tubes.emplace_back(std::move(Tube2));

	auto Tube3 = std::make_unique<Tube>();
	Tube3->Initialize(2, VGet(237.f, 301.f, 3389.f));
	MV1SetupCollInfo(Tube3->handle, tube.handleCol, 4, 4, 4);
	san.tubeCol[2] = Tube3->handleCol;
	lka.tubeCol[2] = Tube3->handleCol;
	san.tubeHandle[2] = Tube3->handle;
	lka.tubeHandle[2] = Tube3->handle;
	tubes.emplace_back(std::move(Tube3));


	timer.Initialize(8, 0, 80);

	san.SetCamera(&_cam);
	san.SetBomb(&sanbomb);
	san.SetDamage(&damage);
	san.SetGimmick(&gimmick);
	san.SetLka(&lka);

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
	lka.SetSan(&san);

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
	damage.SetBomb(&sanbomb, &lkabomb);
	gimmick.Initialize();
	gimmick.SetSanLka(&san, &lka);
	sanbomb.Initialize(san);
	lkabomb.Initialize(lka);
	electrode.Initialize(VGet(63, 301, 2289), false);


	//CSVによる初期化（レベルデザイン時に実装）

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
						auto Slime1 = std::make_unique<Slime>();
						Slime1->Initialize(x, y, z, pH);
						Slime1->SetSan(&san);
						Slime1->SetLka(&lka);
						Slime1->SetSanBomb(&sanbomb);
						Slime1->SetLkaBomb(&lkabomb);
						slimes.emplace_back(std::move(Slime1));
					}
					else if (cnt == 4)
					{
						auto Slime2 = std::make_unique<Slime>();
						Slime2->Initialize(x, y, z, pH);
						Slime2->SetSan(&san);
						Slime2->SetLka(&lka);
						Slime2->SetSanBomb(&sanbomb);
						Slime2->SetLkaBomb(&lkabomb);
						slimes.emplace_back(std::move(Slime2));
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


	//CSVの調整にカメラを追いつかせる
	_cam._vPos.x += (san.vPos.x + lka.vPos.x) / 2.f;
	if (san.vPos.y > lka.vPos.y) {
		_cam._vPos.y += (lka.vPos.y);
	}
	else if (lka.vPos.y > san.vPos.y) {
		_cam._vPos.y += (san.vPos.y);
	}
	else {
		_cam._vPos.y += (san.vPos.y + lka.vPos.y) / 2.f;
	}

	_cam._vPos.z += (san.vPos.z + lka.vPos.z) / 2.f;
	_cam._vTarget.x = ((san.vPos.x + lka.vPos.x) / 2.f);
	_cam._vTarget.y = ((san.vPos.y + lka.vPos.y) / 2.f);
	_cam._vTarget.z = ((san.vPos.z + lka.vPos.z) / 2.f);


	//シャドウマップの生成
	ShadowMapHandle = MakeShadowMap(1024, 1024);

	SetShadowMapLightDirection(ShadowMapHandle, VGet(0, -1, 0));

	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(ShadowMapHandle);

	// シャドウマップへキャラクターモデルの描画
	MV1DrawModel(san.Mhandle);
	MV1DrawModel(lka.Mhandle);

	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	PlayMusic("res/06_Sound/01_BGM/Stage/Confectioner.mp3", DX_PLAYTYPE_LOOP);


	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	MV1DeleteModel(_handleMap);
	MV1DeleteModel(_handleSkySphere);
	san.Terminate();
	lka.Terminate();
	sanbomb.Terminate();
	lkabomb.Terminate();
	elevator.Terminate();
	gimmick.Terminate();
	irondoor.Terminate();
	sanbomb.EffectReset();
	lkabomb.EffectReset();
	sancircle.EffectReset();
	lkacircle.EffectReset();
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
	san.Update(damage, nullptr);
	lka.Update(damage, nullptr);

	damage.Process();
	damage.StageDamage(_handleMap);
	damage.SlimeDamage(slimes);

	if ((respawn2ndPosSan.y <= san.vPos.y && respawn2ndPosSan.z <= san.vPos.z) && (respawn2ndPosLka.y <= lka.vPos.y && respawn2ndPosLka.z <= lka.vPos.z) && !respawn2nd)
	{
		respawn2nd = true;
	}
	else if ((respawn1stPosSan.y <= san.vPos.y && respawn1stPosSan.z <= san.vPos.z) && (respawn1stPosLka.y <= lka.vPos.y && respawn1stPosLka.z <= lka.vPos.z) && !respawn1st)
	{
		respawn1st = true;
	}
	else {}

	if ((san.vPos.y <= -1000.0f) || (lka.vPos.y <= -1000.0f) || (san.HP <= 0) || (lka.HP <= 0))
	{
		Respawn();
	}

	for (auto&& Slimes : slimes) {
		Slimes->Process(san.vPos, lka.vPos, _handleMap, 2.f, Slimes->mypH);
	}

	if (timer.timeup == true)
	{
		Isgameover = true;
		sanbomb.EffectReset();
		sancircle.EffectReset();
		lkabomb.EffectReset();
		lkacircle.EffectReset();
		sanbomb.EffectReset();
		lkabomb.EffectReset();
		//BGM停止
		StopMusic();

		// シャドウマップの削除
		DeleteShadowMap(ShadowMapHandle);

		ChangePanSoundMem(255, san.VOICEdeathSAN);
		ChangePanSoundMem(-255, lka.VOICEdeathLKA);
		PlaySoundMem(san.VOICEdeathSAN, DX_PLAYTYPE_BACK, true);
		PlaySoundMem(lka.VOICEdeathLKA, DX_PLAYTYPE_BACK, true);
		if (gameoverchange == true)
		{
			Terminate();
			ModeServer::GetInstance()->Del(this);
			if ((san.vPos.y <= -1000.0f) || (lka.vPos.y <= -1000.0f) || (san.HP <= 0) || (lka.HP <= 0)) {
				ModeServer::GetInstance()->Add(new ModeGameOver(1, false), 1, "gameover");
			}
			else {
				ModeServer::GetInstance()->Add(new ModeGameOver(1, true), 1, "gameover");
			}
		}
	}

	int Trg;
	int keyold = Key;
	Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	Trg = (Key ^ keyold) & Key;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	int checkKey = PAD_INPUT_10;
	if (Trg & checkKey) {
		sanbomb.EffectReset();
		sancircle.EffectReset();
		lkabomb.EffectReset();
		lkacircle.EffectReset();
		sanbomb.EffectReset();
		lkabomb.EffectReset();
		//BGM停止
		StopMusic();

		// シャドウマップの削除
		DeleteShadowMap(ShadowMapHandle);

		Terminate();

		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame, 1, "stage01");
	}
	timer.Update();
	sanbomb.Update(san);
	lkabomb.Update(lka);
	sancircle.Update(san, lka);
	lkacircle.Update(san, lka);

	electrode.Update(sanbomb, lkabomb);
	elevator.Update(electrode);
	for (int i = 0; i < tubes.size(); ++i) {
		tubes[i]->Update(electrode);
	}

	if (san.goal && lka.goal) {
		//BGM停止
		StopMusic();

		// シャドウマップの削除
		DeleteShadowMap(ShadowMapHandle);

		Terminate();
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeBoss(), 1, "boss");
	}

	return true;
}

bool ModeGame::Render() {
	base::Render();

	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// ライト設定
	SetUseLighting(TRUE);
#if 1	// 平行ライト
	SetGlobalAmbientLight(GetColorF(0.1f, 0.1f, 0.1f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 1));


#endif
#if 0	// ポイントライト
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_vPos, VGet(0, 50.f, 0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	// カメラ設定更新
	_cam._vTarget = VScale(VAdd(san.vPos, lka.vPos), 0.5);
	_cam._vPos = VAdd(_cam._vTarget, VGet(0, 400.f, -500.f));
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

	{
		gimmick.Render();
		for (auto&& Slimes : slimes) {
			Slimes->Render(Slimes->mypH);
		}
	}
	//マップモデルを描画する
	{
		// シャドウマップへの描画の準備
		ShadowMap_DrawSetup(ShadowMapHandle);

		// シャドウマップへキャラクターモデルの描画
		MV1DrawModel(san.Mhandle);
		MV1DrawModel(lka.Mhandle);

		// シャドウマップへの描画を終了
		ShadowMap_DrawEnd();

		SetShadowMapDrawArea(ShadowMapHandle, VAdd(san.vPos, ShadowMapUpVec), VAdd(lka.vPos, ShadowMapDownVec));

		SetUseShadowMap(0, ShadowMapHandle);

		// ステージモデルの描画
		MV1DrawModel(_handleMap);

		// 描画に使用するシャドウマップの設定を解除
		SetUseShadowMap(0, -1);

		MV1SetScale(_handleSkySphere, VGet(2.0f, 2.0f, 2.0f));
		MV1DrawModel(_handleSkySphere);

	}
	// デバッグ表示
#ifdef debug
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
		DrawCapsule3D(VGet(san.vPos.x, san.vPos.y + 30, san.vPos.z), VGet(san.vPos.x, san.vPos.y + 75, san.vPos.z), 30.0f, 8, GetColor(255, 0, 0), GetColor(255, 255, 255), FALSE);
		DrawCapsule3D(VGet(lka.vPos.x, lka.vPos.y + 30, lka.vPos.z), VGet(lka.vPos.x, lka.vPos.y + 75, lka.vPos.z), 30.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), FALSE);
		DrawFormatString(0, 300, GetColor(255, 0, 0), "SANDisk(%f,%f,%f)", gimmick.SANDisk.x, gimmick.SANDisk.y, gimmick.SANDisk.z);
		DrawFormatString(0, 220, GetColor(0, 0, 0), "BlendRate = %f", gimmick.BlendRate);
		DrawFormatString(0, 250, GetColor(0, 0, 0), "hitPolyDimSAN.HitNum = %d", san.hitPolyDimSAN.HitNum);
		DrawFormatString(0, 300, GetColor(0, 0, 0), "SanHitFlag = %d", gimmick.SanHitFlag);
		DrawFormatString(0, 350, GetColor(0, 0, 0), "sanHitFlag = %d", slimes[1]->sanHitFlag);
		DrawFormatString(0, 400, GetColor(0, 0, 0), "sanHitFlag = %d", damage.HitPolySanBomb.HitNum);
	}
#endif
	//マップのUVスクロール
	_UVScroll_U += 0.001f;
	MV1SetFrameTextureAddressTransform(
		_handleSkySphere	// モデルハンドル
		, 0				// UV操作するフレーム番号
		, _UVScroll_U, _UVScroll_V		// UV加算値(def:0.f, 0.f〜1.f ループ)
		, 1.0f, 1.0f					// UV乗算値(def:1.f)
		, 0.0f, 0.0f					// UV回転中心値
		, 0.0f							// UV回転度数（ラジアンで指定）
	);


	lka.Render(damage);
	san.Render(damage);
	sanbomb.Render();
	lkabomb.Render();
	sancircle.Render();
	lkacircle.Render();
	for (auto&& Irondoors : irondoors) {
		Irondoors->Render();
	}
	electrode.Render();
	for (auto&& Tubes : tubes) {
		Tubes->Render();
	}
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
	timer.Render();
	return true;
}

void ModeGame::Respawn()
{
	if (respawn2nd)
	{
		san.vPos = respawn2ndPosSan;
		lka.vPos = respawn2ndPosLka;
	}
	else if (respawn1st)
	{
		san.vPos = respawn1stPosSan;
		lka.vPos = respawn1stPosLka;
	}
	else
	{
		san.vPos = respawnstartSan;
		lka.vPos = respawnstartLka;
	}

	san._status = SAN::STATUS::WAIT;
	lka._status = LKA::STATUS::WAIT;
	san.BackCount = 0;
	lka.BackCount = 0;
	san.vPos.y += 10.f;
	lka.vPos.y += 10.f;
	san.HP = 6;
	lka.HP = 6;
}

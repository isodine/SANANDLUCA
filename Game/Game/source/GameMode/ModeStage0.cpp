
#include "AppFrame.h"
#include "ModeGameOver.h"

std::vector<std::string> splitme00(std::string& input, char delimiter)
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

ModeStage0::ModeStage0() {

}

bool ModeStage0::Initialize() {
	if (!base::Initialize()) { return false; }
	//ステージの種類
	_handleMap = MV1LoadModel("res/07_Stage_map/00_Stage/Stage_00.fbm/Stage_00.mv1");
	_handleSkySphere = MV1LoadModel("res/07_Stage_map/00_Stage/00SkyCube_B/sky.mv1");
	MV1SetPosition(_handleMap, VGet(50.0f, 0.0f, 700.0f));

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

	respawnstartSan = VGet(-30.f, 20.f, 670.f);
	respawnstartLka = VGet(100.f, 20.f, 670.f);

	respawn1stPosSan = VGet(-360.f, 20.f, 2000.f);
	respawn1stPosLka = VGet(461.f, 20.f, 2000.f);

	respawn2ndPosSan = VGet(-151.f, 73.f, 3937.f);
	respawn2ndPosLka = VGet(146.f, 73.f, 3930.f);


	timer.Initialize(9, 9, 99);

	san.SetCamera(&_cam);
	san.SetBomb(&sanbomb);
	san.SetDamage(&damage);
	san.SetLka(&lka);

	san.Initialize();
	san.floorCol = frameMapCollisionfloor;
	san.wallCol = frameMapCollisionwall;
	san.goalColSAN = frameMapCollisiongoalSAN;
	san.stageHandle = _handleMap;

	lka.SetCamera(&_cam);
	lka.SetBomb(&lkabomb);
	lka.SetDamage(&damage);
	lka.SetSan(&san);

	lka.Initialize();
	lka.floorCol = frameMapCollisionfloor;
	lka.wallCol = frameMapCollisionwall;
	lka.goalColLKA = frameMapCollisiongoalLKA;
	lka.stageHandle = _handleMap;

	auto IronDoor1 = std::make_unique<IronDoor>();
	IronDoor1->Initialize(true, VGet(-290.f, 25.f, 2129.f));
	irondoors.emplace_back(std::move(IronDoor1));

	auto IronDoor2 = std::make_unique<IronDoor>();
	IronDoor2->Initialize(false, VGet(421.f, 25.f, 2118.f));
	irondoors.emplace_back(std::move(IronDoor2));

	auto IronDoor3 = std::make_unique<IronDoor>();
	IronDoor3->Initialize(false, VGet(-2.f, 135.f, 4301.f));
	irondoors.emplace_back(std::move(IronDoor3));

	auto IronDoor4 = std::make_unique<IronDoor>();
	IronDoor4->Initialize(true, VGet(-3.f, 230.f, 5849.f));
	irondoors.emplace_back(std::move(IronDoor4));

	damage.Initialize(&san, &lka);
	damage.SetBomb(&sanbomb, &lkabomb);
	sanbomb.Initialize(san);
	lkabomb.Initialize(lka);


	//CSVによる初期化（レベルデザイン時に実装）

	std::ifstream ifs("res/test.csv");

	std::string line;
	std::vector<std::string> strresult;
	std::vector<int> intresult;
	int x, y, z, pH;
	int cnt = 0;
	while (std::getline(ifs, line)) {

		std::vector < std::string > strvec = splitme00(line, ',');

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
	_cam._vPos.y += (san.vPos.y + lka.vPos.y) / 2.f;
	_cam._vPos.z += (san.vPos.z + lka.vPos.z) / 2.f;
	_cam._vTarget.x = ((san.vPos.x + lka.vPos.x) / 2.f);
	_cam._vTarget.y = ((san.vPos.y + lka.vPos.y) / 2.f);
	_cam._vTarget.z = ((san.vPos.z + lka.vPos.z) / 2.f);

	//UVスクロール
	_UVScroll_U = 0.0f;
	_UVScroll_V = 0.0f;

	//シャドウマップの生成
	ShadowMapHandle = MakeShadowMap(1024, 1024);

	SetShadowMapLightDirection(ShadowMapHandle, VGet(0, -1, 0));

	// シャドウマップへの描画の準備
	ShadowMap_DrawSetup(ShadowMapHandle);

	// シャドウマップへステージモデルの描画
	MV1DrawModel(_handleMap);

	// シャドウマップへキャラクターモデルの描画
	MV1DrawModel(san.Mhandle);
	MV1DrawModel(lka.Mhandle);

	// シャドウマップへの描画を終了
	ShadowMap_DrawEnd();

	PlayMusic("res/06_Sound/01_BGM/Stage/Confectioner.mp3", DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeStage0::Terminate() {
	base::Terminate();
	MV1DeleteModel(_handleMap);
	MV1DeleteModel(_handleSkySphere);
	san.Terminate();
	lka.Terminate();
	sanbomb.Terminate();
	lkabomb.Terminate();
	damage.Terminate();
	sanbomb.EffectReset();
	lkabomb.EffectReset();
	sancircle.EffectReset();
	lkacircle.EffectReset();
	return true;
}

bool ModeStage0::Process() {
	base::Process();

	san.Update(damage, &irondoors);
	lka.Update(damage, &irondoors);
	damage.Process();
	timer.Update();
	sanbomb.Update(san);
	lkabomb.Update(lka);
	sancircle.Update(san, lka);
	lkacircle.Update(san, lka);


	damage.StageDamage(_handleMap);

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
		ModeServer::GetInstance()->Add(new ModeStage0, 1, "stage00");
	}

	for (auto&& Irondoors : irondoors) {
		if (!Irondoors->melt) {
			Irondoors->Update(sanbomb, lkabomb);
		}
	}

	if (timer.timeup == true)
	{
		//BGM停止
		StopMusic();

		//BGM停止
		StopMusic();

		// シャドウマップの削除
		DeleteShadowMap(ShadowMapHandle);
		sanbomb.EffectReset();
		sancircle.EffectReset();
		lkabomb.EffectReset();
		lkacircle.EffectReset();
		sanbomb.EffectReset();
		lkabomb.EffectReset();
		ChangePanSoundMem(255, san.VOICEdeathSAN);
		ChangePanSoundMem(-255, lka.VOICEdeathLKA);
		PlaySoundMem(san.VOICEdeathSAN, DX_PLAYTYPE_BACK, true);
		PlaySoundMem(lka.VOICEdeathLKA, DX_PLAYTYPE_BACK, true);
		Terminate();

		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(0, true), 1, "gameover");
	}

	if ((san.goal && lka.goal)) {
		//BGM停止
		StopMusic();

		// シャドウマップの削除
		DeleteShadowMap(ShadowMapHandle);
		Terminate();
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGame(), 1, "stage01");
	}

	return true;
}

bool ModeStage0::Render() {
	base::Render();

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

		//マップのUVスクロール
		_UVScroll_U -= 0.001f;
		MV1SetFrameTextureAddressTransform(
			_handleSkySphere	// モデルハンドル
			, 0				// UV操作するフレーム番号
			, _UVScroll_U, _UVScroll_V		// UV加算値(def:0.f, 0.f〜1.f ループ)
			, 1.0f, 1.0f					// UV乗算値(def:1.f)
			, 0.0f, 0.0f					// UV回転中心値
			, 0.0f							// UV回転度数（ラジアンで指定）
		);
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
	for (auto&& Irondoors : irondoors) {
		Irondoors->Render();
	}
	lka.Render(damage);
	san.Render(damage);
	sanbomb.Render();
	lkabomb.Render();
	sancircle.Render();
	lkacircle.Render();
	timer.Render();
	return true;
}

void ModeStage0::Respawn()
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

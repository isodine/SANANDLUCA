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

	//// モデルデータのロード（テクスチャも読み込まれる）
	//_handle = MV1LoadModel("res/SDChar/SDChar.mv1");
	//_attach_index = -1;		// アニメーションアタッチはされていない

	//// 再生時間の初期化
	//_total_time = 0.f;
	//_play_time = 0.0f;
	//// 位置,向きの初期化
	//_vPos = VGet(0, 0, 0);
	//_vDir = VGet(0, 0, -1);		// キャラモデルはデフォルトで-Z方向を向いている
	//カメラ設定
	_cam._vTarget = VGet(0,0,0);
	_cam._vPos = VGet(0,1000,-300);

	// マップ
	_handleMap = MV1LoadModel("res/07_Stage_map/Boss_Stage/04_Stage_Boss.mv1");
	MV1SetPosition(_handleMap, VGet(50.0f, 0.0f, 700.0f));
	_handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1");

	// コリジョン情報の生成
	frameMapCollisionfloor = MV1SearchFrame(_handleMap, "coStage_floor1");
	frameMapCollisionwall = MV1SearchFrame(_handleMap, "coStage_wall1");
	MV1SetupCollInfo(_handleMap, frameMapCollisionfloor, 16, 16, 16);
	// コリジョンのフレームを描画しない設定
	MV1SetFrameVisible(_handleMap, frameMapCollisionfloor, FALSE);
	MV1SetFrameVisible(_handleMap, frameMapCollisionwall, FALSE);
	/*MV1SetFrameVisible(_handleMap, 0, FALSE);
	MV1SetFrameVisible(_handleMap, 1, FALSE);*/

	//マスクの試験運用
	MaskHandle = LoadMask("res/San_Lka_Mask.png");
	CreateMaskScreen();

	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet(0, 300.f, -400.f);
	_cam._vTarget = VGet(0, 60, 0);
	_cam._clipNear = 2.f;
	_cam._clipFar = 20000.f;


	//フォグを使ってみる
	//SetFogEnable(TRUE);

	// フォグの色を設定
	//SetFogColor(255, 255, 255);

	// フォグの開始距離、終了距離を設定
	//SetFogStartEnd(0.0f, 3000.0f);

	// その他初期化
	_bViewCollision = FALSE;

	GameMode = 1;

	throughtime = 0.0f;
	height = 0.0f;

	san.SetCamera(&_cam);
	san.SetBomb(&sanbomb);
	san.SetDamage(&damage);

	san.Initialize();
	san.floorCol = frameMapCollisionfloor;
	san.wallCol = frameMapCollisionwall;
	san.stageHandle = _handleMap;

	lka.SetCamera(&_cam);
	lka.SetBomb(&sanbomb);
	lka.SetDamage(&damage);

	lka.Initialize();
	lka.floorCol = frameMapCollisionfloor;
	lka.wallCol = frameMapCollisionwall;
	lka.stageHandle = _handleMap;

	damage.Initialize(&san, &lka);
	damage.stageFlag = false;
	//enemy.Initialize();
	//gimmick.Initialize();
	//gimmick.SetSanLka(&san, &lka);
	//CSVによる初期化（レベルデザイン時に実装）

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

	//CSVの調整にカメラを追いつかせる
	_cam._vPos.x += (san.vPos.x + lka.vPos.x) / 2.f;
	_cam._vPos.y += (san.vPos.y + lka.vPos.y) / 2.f;
	_cam._vPos.z += (san.vPos.z + lka.vPos.z) / 2.f;
	_cam._vTarget.x = ((san.vPos.x + lka.vPos.x) / 2.f);
	_cam._vTarget.y = ((san.vPos.y + lka.vPos.y) / 2.f);
	_cam._vTarget.z = ((san.vPos.z + lka.vPos.z) / 2.f);

	PlayMusic("res/06_Sound/01_BGM/Confectioner.mp3", DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeBoss::Terminate() {
	ModeBase::Terminate();
	return true;
}

bool ModeBoss::Process() {
	ModeBase::Process();

	//for (auto&& SanLka : sanlka) {
	//	SanLka->Update();
	//}-
	sanbomb.Update(san);
	san.SetOnBalance(gimmick.GetSanHitFlag());
	lka.SetOnBalance(gimmick.GetLkaHitFlag());
	san.Update();
	lka.Update();
	damage.Process();
	//enemy.Slime(san.vPos, lka.vPos, _handleMap, 1.0f);
	//gimmick.Balance(san.vPos, lka.vPos);

	if ((san.vPos.y <= -1000.0f) || (lka.vPos.y <= -1000.0f) || (damage.SanHP <= 0) || (damage.LkaHP <= 0))
	{
		StopMusic();
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "gameover");
	}

	return true;
}

bool ModeBoss::Render() {
	ModeBase::Render();

	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	// ライト設定
	SetUseLighting(TRUE);
#if 1	// 平行ライト
	SetGlobalAmbientLight(GetColorF(0.1f, 0.1f, 0.1f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 1));
	//SetLightEnable(FALSE);
	//SetLightDirection(VSub(_cam._vTarget, _cam._vPos));

	/*LightHandle = CreateDirLightHandle(VGet(0.0f, 0.0f, 1.0f));
	SetLightAmbColorHandle(LightHandle, GetColorF(0.5f, 0.0f, 0.0f, 0.0f));*/

#endif
#if 0	// ポイントライト
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_vPos, VGet(0, 50.f, 0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	// カメラ設定更新
	
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

	// 0,0,0を中心に線を引く
	{
		//float linelength = 1000.f;
		//VECTOR v = { 0, 0, 0 };
		//DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		//DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		//DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// カメラターゲットを中心に短い線を引く
	{
		float linelength = 10.f;
		VECTOR v = _cam._vTarget;
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// 再生時間をセットする
	//MV1SetAttachAnimTime(_handle, _attach_index, _play_time);

	{
		//gimmick.Render();
		//enemy.SlimeRender(enemy.slimePos);
		// コリジョン判定用ラインの描画
		//if (_bViewCollision) {
		//	DrawLine3D(VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));
		//}
	}
	sanbomb.Render();
	// マップモデルを描画する
	{
		MV1SetScale(_handleSkySphere, VGet(2.0f, 2.0f, 2.0f));
		MV1DrawModel(_handleSkySphere);

		MV1DrawModel(_handleMap);
		//DrawMask(0, 0, MaskHandle, DX_MASKTRANS_BLACK);
	}
	san.Render();
	lka.Render();
	// デバッグ表示
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
	}
	damage.Render();
	return true;
}

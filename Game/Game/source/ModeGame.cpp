
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

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

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	// モデルデータのロード（テクスチャも読み込まれる）
	_handle = MV1LoadModel("res/SDChar/SDChar.mv1");
	_model = MV1LoadModel("res/Sun/モデル（テクスチャ込み）/SUN.mv1");
	_attach_index = -1;		// アニメーションアタッチはされていない
	//_effectResourceHandle = LoadEffekseerEffect("res/san_bomb_1.6_2/san_bomb_loop_01.efkefc", 10.0f);

	// 再生時間の初期化
	_total_time = 0.f;
	_play_time = 0.0f;
	// 位置,向きの初期化
	_vPos = VGet(0, 0, 0);
	_vDir = VGet(0, 0, -1);		// キャラモデルはデフォルトで-Z方向を向いている
	//oldcount = 0;
	// マップ
	_handleMap = MV1LoadModel("res/0.3.mv1");
	_handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1");

	// コリジョン情報の生成
	_frameMapCollision = MV1SearchFrame(_handleMap, "Comp_floor_01");
	MV1SetupCollInfo(_handleMap, _frameMapCollision, 16, 16, 16);
	// コリジョンのフレームを描画しない設定
	MV1SetFrameVisible(_handleMap, _frameMapCollision, TRUE);
	// 腰位置の設定
	_colSubY = 60.f;


	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet(0, 120.f, -300.f);
	_cam._vTarget = VGet(0, 60, 0);
	_cam._clipNear = 2.f;
	_cam._clipFar = 10000.f;

	// その他初期化
	_bViewCollision = TRUE;

	throughtime = 0.0f;
	height = 0.0f;

	san.Initialize();
	lka.Initialize();
	damage.Initialize(&san, &lka);

	//CSVによる初期化（レベルデザイン時に実装）

	/*std::ifstream ifs("res/test.csv");

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
	}*/


	//auto san = std::make_unique<SAN>();
	//auto lka = std::make_unique<LKA>();
	//san->Initialize();
	//lka->Initialize();
	//sanlka.emplace_back(std::move(san));
	//sanlka.emplace_back(std::move(lka));

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();
	//DeleteEffekseerEffect(_effectResourceHandle);
	return true;
}

bool ModeGame::Process() {
	base::Process();

	//for (auto&& SanLka : sanlka) {
	//	SanLka->Update();
	//}

	san.Update(_cam);
	lka.Update(_cam);
	damage.Process();
	//int key = ApplicationMain::GetInstance()->GetKey2P();
	//int trg = ApplicationMain::GetInstance()->GetTrg2P();

	//// 処理前のステータスを保存しておく
	//STATUS oldStatus = _status;

	int keyoldEf = _KeyEf;
	_KeyEf = GetJoypadInputState(DX_INPUT_PAD1);
	_TrgEf = (_KeyEf ^ keyoldEf) & _KeyEf;

	if (_gTrgEf & PAD_INPUT_7) {	// Q
		// 角度変更
		// Y軸回転
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float rad = atan2(sz, sx);
		float length = sqrt(sz * sz + sx * sx);
		if (_gKeyEf & PAD_INPUT_LEFT) { rad -= 0.05f; }
		if (_gKeyEf & PAD_INPUT_RIGHT) { rad += 0.05f; }
		_cam._vPos.x = _cam._vTarget.x + cos(rad) * length;
		_cam._vPos.z = _cam._vTarget.z + sin(rad) * length;

		// Y位置
		if (_gKeyEf & PAD_INPUT_DOWN) { _cam._vPos.y -= 5.f; }
		if (_gKeyEf & PAD_INPUT_UP) { _cam._vPos.y += 5.f; }
	}
	sanbomb.Update(san);

	//if (_gTrgEf & PAD_INPUT_9 && oldcount == 0)
	//{
	//	old


	//if (_isthrow == 0) 
	//{
	//	_position_x = san.vPos.x;
	//	_position_y = san.vPos.y + 150;
	//	_position_z = san.vPos.z;
	//}
	//if (_TrgEf & PAD_INPUT_6 && _isEffect == 0)
	//{
	//	_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
	//	// 再生中のエフェクトを移動する。
	//	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
	//	//_position_x += 0.2f;
	//	SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 0.1f, 0.1f, 0.1f);

	//	_isEffect = 1;

	//	oldcount = GetNowCount();

	//	//if (GetModeCount() % 60 == 0)
	//	//{
	//	//	_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
	//	//	// 再生中のエフェクトを移動する。
	//	//	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
	//	//	//_position_x += 0.2f;
	//	//	SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 0.1f, 0.1f, 0.1f);

	//	//	_isEffect = 1;

	//	//}
	//}
	//SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
	//UpdateEffekseer3D();

	////if (_TrgEf & PAD_INPUT_5 && _isEffect == 1)
	////{
	////	_isthrow = 1;
	////}
	////if (_isthrow == 1)
	////{
	////	bombthrow();
	////}
	////_position_y += _hight;
	////if (_position_y <= 0)
	////{
	////	_hight = 0.0f;
	////	_isEffect = 0;
	////	_isthrow = 0;

	////}


	//if (oldcount > 0)
	//{
	//	auto nowCount = GetNowCount();
	//	if (nowCount - oldcount >= 2000)
	//	{
	//		if (_TrgEf & PAD_INPUT_6 && _isEffect == 1)
	//		{
	//			_isthrow = 1;
	//		}
	//		if (_isthrow == 1)
	//		{
	//			bombthrow();
	//		}
	//		_position_y += _hight;
	//		if (_position_y <= 0)
	//		{
	//			_hight = 0.0f;
	//			_isEffect = 0;
	//			_isthrow = 0;
	//			oldcount = 0;
	//		}
	//	}
	//}



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
	SetGlobalAmbientLight(GetColorF(1.0f, 1.0f, 1.0f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 1));
	//SetLightDirection(VSub(_cam._vTarget, _cam._vPos));

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
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
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

	// モデルを描画する

	{
		// 位置
		//MV1SetPosition(_handle, _vPos);
		//// 向きからY軸回転を算出
		//VECTOR vRot = { 0,0,0 };
		//vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);		// モデルが標準でどちらを向いているかで式が変わる(これは-zを向いている場合)
		//MV1SetRotationXYZ(_handle, vRot);
		//// 描画

		//MV1DrawModel(_handle);
		//for (auto&& SanLka : sanlka) {
		//	SanLka->Render();
		//}

		san.Render();
		lka.Render();


		// コリジョン判定用ラインの描画
		if (_bViewCollision) {
			DrawLine3D(VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));
		}

	}

	// マップモデルを描画する
	{
		MV1DrawModel(_handleSkySphere);
		MV1DrawModel(_handleMap);
	}

	// カメラ情報表示
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
	}
	damage.Render();
	sanbomb.Render();
	//int AttachIndex;
	//float TotalTime;
	//MV1SetMaterialDrawBlendParam(san.Mhandle, 0, 125);
	////MV1SetScale(_model, VGet(3.0f, 3.0f, 3.0f));
	//MV1SetPosition(san.Mhandle, VGet(0.0f, 40.0f, 0.0f));
	//AttachIndex = MV1AttachAnim(san.Mhandle, 1, -1, FALSE);
	//TotalTime = MV1GetAttachAnimTotalTime(san.Mhandle, AttachIndex);
		// 再生時間を進める
	//PlayTime += 60.0f;

		//再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	//	if (PlayTime >= TotalTime)
	//	{
	//		PlayTime = 0.0f;
	//	}
	//MV1SetAttachAnimTime(san.Mhandle, AttachIndex, PlayTime);
	//MV1DrawModel(san.Mhandle);



		// DXライブラリのカメラとEffekseerのカメラを同期する。
		/*Effekseer_Sync3DSetting();
		
		DrawEffekseer3D_Begin();
		DrawEffekseer3D_Draw(_playingEffectHandle);
		DrawEffekseer3D_End();
		if (_isEffect == 0)
		{
			StopEffekseer3DEffect(_playingEffectHandle);
		}*/


	return true;
}

void ModeGame::charJump() {
	height += 10.0f - throughtime;
	throughtime += 0.3f;

}

//void ModeGame::bombthrow()
//{
//	_hight += 1.0f - _throw;
//	_throw += 0.5f;
//
//}



/*****************************************************************//**
 * \file   Slime.cpp
 * \brief  スライムの動作全般
 *
 * \author 土屋　涼乃
 * \date   December 2022
 * \details December 2022以降に大幅改変あり
 *********************************************************************/

void Slime::Initialize(float x, float y, float z, int pH) {
	PlayTime = 0.0f;
	slimePos = VGet(x, y, z);
	slimeDir = VGet(0, 0, 0);
	slimeError = 2.0;
	mypH = pH;
	slimeHP = 2;
	_status = STATUS::NONE;
	AttachAnim = -1;
	acidcount = 0;
	alkalicount = 0;
	sanHitFlag = false;
	lkaHitFlag = false;
	acidPos[0] = { VGet(140, 567, 7105) }; 
	acidPos[1] = { VGet(140, 567, 6744) };
	acidPos[2] = { VGet(344, 567, 6744) };
	acidPos[3] = { VGet(344, 567, 7105) };

	alkaliPos[0] = { VGet(-99, 567, 7105) };
	alkaliPos[1] = { VGet(-99, 567, 6744) }; 
	alkaliPos[2] = { VGet(-303, 567, 6744) };
	alkaliPos[3] = { VGet(-303, 567, 7105) };

	SearchPosMinX = -392;
	SearchPosMaxX = 415;
	SearchPosMinZ = 6647;
	SearchPosMaxZ = 7178;

	acidPassedCount = 0;
	alkaliPassedCount = 0;

	acidDieFlag = false;
	alkaliDieFlag = false;

	MV1SetupCollInfo(slimeHandle, 2, 8, 8, 8);
	slimeHandle = MV1LoadModel("res/slime/slime_multimotion.mv1");
	acidHandle = LoadGraph("res/slime/acidslime_tex.png");
	alkaliHandle = LoadGraph("res/slime/alkalislime_tex.png");

	if (mypH == 1) {
		//slimePos = acidPos[0];
		slimePos = acidPos[0];
		slimeTargetPos = acidPos[1];
	}
	if (mypH == 2) {
		//slimePos = alkaliPos[0];
		slimePos = alkaliPos[0];
		slimeTargetPos = alkaliPos[1];
	}
}

void Slime::Terminate() {

}

void Slime::SetSan(SAN* san) {
	_san = san;
}

void Slime::SetLka(LKA* lka) {
	_lka = lka;
}

void Slime::SetSanBomb(SanBomb* sanbomb) {
	_sanbomb = sanbomb;
}

void Slime::SetLkaBomb(LkaBomb* lkabomb) {
	_lkabomb = lkabomb;
}

void Slime::Process(VECTOR SanPos, VECTOR LkaPos, int HandleMap, float speed, int mypH) {

	STATUS oldStatus = _status;
	VECTOR oldAcidPos = slimePos;
	VECTOR oldAlkaliPos = slimePos;
	MV1RefreshCollInfo(slimeHandle, 2);
	_rotationMatrix = MMult(MMult(MGetRotX(slimeDir.x), MGetRotY(slimeDir.y)), MGetRotZ(slimeDir.z));

	forward = { VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	// 画面内にキャラクターが入っていないかどうかを描画する
			//TRUEは入ってない、FALSEは入ってる
	if (CheckCameraViewClip(slimePos) == TRUE)
	{
		// 画面外に出た。元の座標に戻す
		slimePos = oldAcidPos;
		forward = { 0,0,0 };
	}
	
	//タイプとボムの種類によってダメージを受ける
	if(mypH == 2 && !alkaliDieFlag){
		SANhitPolyDimAlkali = MV1CollCheck_Sphere(slimeHandle, 2, _sanbomb->vPos, _sanbomb->sphereSize);
		LKAhitPolyDimAlkali = MV1CollCheck_Sphere(slimeHandle, 2, _lkabomb->vPos, _lkabomb->sphereSize);
		if (SANhitPolyDimAlkali.HitNum >= 1) {
			slimeHP -= 2;
		}
		if (LKAhitPolyDimAlkali.HitNum >= 1) {
			slimeHP -= 1;
		}
		if (slimeHP <= 0) {
			alkaliDieFlag = true;
		}
		
		if (SanPos.x >= SearchPosMinX && SanPos.x <= SearchPosMaxX && SanPos.z >= SearchPosMinZ && SanPos.z <= SearchPosMaxZ) {
			SanTargeting(SanPos, 2.3);
			if (sanDistance < 130)
			{
				AcidJump(SanPos);
			}
			else {
				alkalicount = 0;
				sanHitFlag = false;
			}
		}
		else {
			AlkaliWalk(1.4f);
		}
  }
	if(mypH == 1 &&!acidDieFlag){
		SANhitPolyDimAcid = MV1CollCheck_Sphere(slimeHandle, 2, _sanbomb->vPos, _sanbomb->sphereSize);
		LKAhitPolyDimAcid = MV1CollCheck_Sphere(slimeHandle, 2, _lkabomb->vPos, _lkabomb->sphereSize);
		if (SANhitPolyDimAcid.HitNum >= 1) {
			slimeHP -= 1;
		}
		if (LKAhitPolyDimAcid.HitNum >= 1) {
			slimeHP -= 2;
		}
		if (slimeHP <= 0) {
			alkaliDieFlag = true;
		}
		if (LkaPos.x >= SearchPosMinX && LkaPos.x <= SearchPosMaxX && LkaPos.z >= SearchPosMinZ && LkaPos.z <= SearchPosMaxZ) {
			LkaTargeting(LkaPos, 2.3);
			if (lkaDistance < 130)
			{
				AlkaliJump(LkaPos);
			}
			else {
			acidcount = 0;
			lkaHitFlag = 0;
			}
		}
		else {
			AcidWalk(1.4f);
		}
	}
	// モーションが切り替わったか？
	if (oldStatus == _status) {
		PlayTime += 1.0f;
		if (PlayTime >= TotalTime)
		{
			PlayTime = 0.0f;
		}
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (AttachAnim != -1) {
			MV1DetachAnim(slimeHandle, AttachAnim);
			AttachAnim = -1;
		}
		// ステータスに合わせてアニメーションをアタッチする
		switch (_status) {
		case STATUS::WALK_KAI:
			AttachAnim = MV1AttachAnim(slimeHandle, 2, -1, FALSE);//歩きモーションをアタッチする
			break;
		case STATUS::ATTACK:
			AttachAnim = MV1AttachAnim(slimeHandle, 0, -1, FALSE);//攻撃モーションをアタッチする
			break;
		case STATUS::HIT:
			AttachAnim = MV1AttachAnim(slimeHandle, 1, -1, FALSE);//ダメージモーションをアタッチする
			break;
		}
		TotalTime = MV1GetAttachAnimTotalTime(slimeHandle, AttachAnim);
		PlayTime = 0.0f;
	}

	MV1SetAttachAnimTime(slimeHandle, AttachAnim, PlayTime);
}

void Slime::Render(int pH) {
	
	if (mypH == 1 && !acidDieFlag) {
		MV1SetPosition(slimeHandle, slimePos);
		MV1SetScale(slimeHandle, VGet(3.0f, 3.0f, 3.0f));
		MV1SetRotationXYZ(slimeHandle, slimeDir);
		MV1SetTextureGraphHandle(slimeHandle, 0, acidHandle, FALSE);
		MV1SetTextureGraphHandle(slimeHandle, 1, acidHandle, FALSE);
		MV1DrawModel(slimeHandle);
	}
	else if (mypH == 2 && !alkaliDieFlag) {
		MV1SetPosition(slimeHandle, slimePos);
		MV1SetScale(slimeHandle, VGet(3.0f, 3.0f, 3.0f));
		MV1SetRotationXYZ(slimeHandle, slimeDir);
		MV1SetTextureGraphHandle(slimeHandle, 0, alkaliHandle, FALSE);
		MV1SetTextureGraphHandle(slimeHandle, 1, alkaliHandle, FALSE);
		MV1DrawModel(slimeHandle);
	}

}

//アルカリ性スライムの攻撃
void Slime::AcidJump(VECTOR SanPos) {

	_status = STATUS::ATTACK;
	VECTOR forward{ VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	VECTOR up{ 0.0f,0.1f,0.0f };
	float spd = 2.0f;
	hitPolyDim1 = MV1CollCheck_Capsule(slimeHandle, 2,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);
	alkalicount += 1;
		if (hitPolyDim1.HitNum >= 1) {
			sanHitFlag = true;
		}
		
		if (alkalicount == 1) {
			slimeDir.y = atan2(SanPos.x, SanPos.z);
			forward = VNorm(VSub(SanPos, slimePos));
		}
		if (alkalicount <= 40 && alkalicount > 20) {
			slimePos = VAdd(slimePos, VScale(forward, 3.0f));
			slimePos = VAdd(slimePos, VScale(up, 20.0f));
		}
		else if (alkalicount > 40 && alkalicount != 61) {
			if (sanHitFlag == true) {
				slimePos = VSub(slimePos, VScale(forward, 6.0f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
			else if (sanHitFlag == false) {
				slimePos = VAdd(slimePos, VScale(forward, 0.5f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
			if (slimePos.y <= 567) {
				slimePos.y = 567;
			}
		}
		else if (alkalicount == 61) {
			slimePos.y = 567;
			sanHitFlag = false;
			alkalicount = 0;
		}
	MV1CollResultPolyDimTerminate(hitPolyDim1);
}

//酸性スライムの攻撃
void Slime::AlkaliJump(VECTOR LkaPos) {
	_status = STATUS::ATTACK;
	VECTOR forward{ VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	VECTOR up{ 0.0f,0.1f,0.0f };
	float spd = 2.0f;
	hitPolyDim2 = MV1CollCheck_Capsule(slimeHandle, 2,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);;
	acidcount += 1;
		if (hitPolyDim2.HitNum >= 1) {
			lkaHitFlag = true;
		}

		if (acidcount == 1) {
			slimeDir.y = atan2(LkaPos.x, LkaPos.z);
			forward = VNorm(VSub(LkaPos, slimePos));
		}
		if (acidcount <= 40 && acidcount > 20) {
			slimePos = VAdd(slimePos, VScale(forward, 3.0f));
			slimePos = VAdd(slimePos, VScale(up, 20.0f));
		}
		else if (acidcount > 40 && acidcount != 61) {
			if (lkaHitFlag == true) {
				slimePos = VSub(slimePos, VScale(forward, 6.0f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
			else if (lkaHitFlag == false) {
				slimePos = VAdd(slimePos, VScale(forward, 0.5f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
			if (slimePos.y <= 567) {
				slimePos.y = 567;
			}
		}
		else if (acidcount == 61) {
			slimePos.y = 567;
			lkaHitFlag = false;
			acidcount = 0;
		}
	MV1CollResultPolyDimTerminate(hitPolyDim2);
}

//酸性スライムの巡回
void Slime::AcidWalk(float speed) {
	_status = STATUS::WALK_KAI;

		if (abs(acidPos[acidPassedCount + 1].x - slimePos.x) <= slimeError && abs(acidPos[acidPassedCount + 1].z - slimePos.z) <= slimeError) {
			slimePos = acidPos[acidPassedCount + 1];
			slimeTargetPos = acidPos[acidPassedCount + 2];
			acidPassedCount += 1;
			if (acidPassedCount == 3) {
				slimeTargetPos = acidPos[0];
				acidPassedCount = -1;
			}
		}
		forward = VNorm(VSub(slimeTargetPos, slimePos));
		slimeDir.y = atan2(forward.x * -1, forward.z * -1);
		slimePos = VAdd(slimePos, VScale(forward, speed));
}

//アルカリ性スライムの巡回
void Slime::AlkaliWalk(float speed) {
	_status = STATUS::WALK_KAI;
		if (abs(alkaliPos[alkaliPassedCount + 1].x - slimePos.x) <= slimeError && abs(alkaliPos[alkaliPassedCount + 1].z - slimePos.z) <= slimeError) {
			slimePos = alkaliPos[alkaliPassedCount + 1];
			slimeTargetPos = alkaliPos[alkaliPassedCount + 2];
			alkaliPassedCount += 1;
			if (alkaliPassedCount == 3) {
				slimeTargetPos = alkaliPos[0];
				alkaliPassedCount = -1;
			}
		}
		forward = VNorm(VSub(slimeTargetPos, slimePos));
		slimeDir.y = atan2(forward.x * -1, forward.z * -1);
		slimePos = VAdd(slimePos, VScale(forward, speed));
}

//アルカリ性スライムがサンを追いかける
void Slime::SanTargeting(VECTOR SanPos, float speed) {
		sanPos = VNorm(VSub(SanPos, slimePos));
		sanDistance = VSize(VSub(SanPos, slimePos));
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos = VAdd(slimePos, VScale(sanPos, speed));
}

//酸性スライムがルカを追いかける
void Slime::LkaTargeting(VECTOR LkaPos, float speed) {
		lkaPos = VNorm(VSub(LkaPos, slimePos));
		lkaDistance = VSize(VSub(LkaPos, slimePos));
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos = VAdd(slimePos, VScale(lkaPos, speed));
}
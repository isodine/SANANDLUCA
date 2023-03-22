void Slime::Initialize(float x, float y, float z, int pH) {
	PlayTime = 0.0f;
	slimePos = VGet(x, y, z);
	slimeDir = VGet(0, 0, 0);
	slimeError = 2.0;
	mypH = pH;
	_status = STATUS::NONE;
	AttachAnim = -1;
	acidcount = 0;
	alkalicount = 0;
	slimeAttackFlag = false;
	sanHitFlag = false;
	lkaHitFlag = false;
	//エラーが起きるならここ
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

	asidPassedCount = 0;
	alkaliPassedCount = 0;

	MV1SetupCollInfo(slimeHandle, 2, 8, 8, 8);
	slimeHandle = MV1LoadModel("res/slime/slime_multimotion.mv1");
	acidHandle = LoadGraph("res/slime/acidslime_tex.png");
	alkaliHandle = LoadGraph("res/slime/alkalislime_tex.png");

	if (mypH == 1) {
		acidSlimePos = acidPos[0];
		slimeTargetPos = acidPos[1];
	}
	if (mypH == 2) {
		alkaliSlimePos = alkaliPos[0];
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

void Slime::Process(VECTOR SanPos, VECTOR LkaPos, int HandleMap, float speed) {

	STATUS oldStatus = _status;
	VECTOR oldPos = slimePos;
	MV1RefreshCollInfo(slimeHandle, 2);
	_rotationMatrix = MMult(MMult(MGetRotX(slimeDir.x), MGetRotY(slimeDir.y)), MGetRotZ(slimeDir.z));

	forward = { VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	// 画面内にキャラクターが入っていないかどうかを描画する
			//TRUEは入ってない、FALSEは入ってる
	if (CheckCameraViewClip(slimePos) == TRUE)
	{
		// 画面外に出た。元の座標に戻す
		slimePos = oldPos;
		forward = { 0,0,0 };
	}
	
		if (_san->vPos.x >= SearchPosMinX && _san->vPos.x <= SearchPosMaxX && _san->vPos.z >= SearchPosMinZ && _san->vPos.z <= SearchPosMaxZ) {
			SanTargeting(_san->vPos, 1.0);
		}
		else {
			AsidWalk(1.0f);
		}

		if (_lka->vPos.x >= SearchPosMinX && _lka->vPos.x <= SearchPosMaxX && _lka->vPos.z >= SearchPosMinZ && _lka->vPos.z <= SearchPosMaxZ) {
			LkaTargeting(_lka->vPos, 1.0);
		}
		else {
			AlkaliWalk(1.0f);
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

void Slime::Render(VECTOR Pos, int pH) {
	MV1SetPosition(slimeHandle, Pos);
	MV1SetScale(slimeHandle, VGet(3.0f, 3.0f, 3.0f));
	MV1SetRotationXYZ(slimeHandle, slimeDir);
	if (mypH == 1) {
		MV1SetTextureGraphHandle(slimeHandle, 0, acidHandle, FALSE);
		MV1SetTextureGraphHandle(slimeHandle, 1, acidHandle, FALSE);
		MV1DrawModel(slimeHandle);
	}
	else if (mypH == 2) {
		MV1SetTextureGraphHandle(slimeHandle, 0, alkaliHandle, FALSE);
		MV1SetTextureGraphHandle(slimeHandle, 1, alkaliHandle, FALSE);
		MV1DrawModel(slimeHandle);
	}

}

void Slime::AsidJump(VECTOR SanPos) {
	if (!slimeAttackFlag) {
		return;
	}
	_status = STATUS::ATTACK;
	VECTOR forward{ VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	VECTOR up{ 0.0f,0.1f,0.0f };
	float spd = 2.0f;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim1;
	if (mypH == 2) {
		hitPolyDim1 = MV1CollCheck_Capsule(slimeHandle, 2,
			VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);

		if (hitPolyDim1.HitNum >= 1) {
			sanHitFlag = true;
		}

		forward = VScale(forward, spd);
		alkalicount += 1;
		if (alkalicount == 1) {
			slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		}
		if (alkalicount <= 40 && alkalicount >= 20) {
			slimePos = VAdd(slimePos, VScale(forward, 3.0f));
			slimePos = VAdd(slimePos, VScale(up, 20.0f));
		}
		else if (alkalicount > 40 && alkalicount != 61) {
			if (sanHitFlag == true) {
				slimePos = VSub(slimePos, VScale(forward, 4.0f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
			else if (lkaHitFlag == false) {
				slimePos = VAdd(slimePos, VScale(forward, 0.5f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
		}
		else if (alkalicount == 61) {
			lkaHitFlag == false;
		}
	}
	MV1CollResultPolyDimTerminate(hitPolyDim1);
}

void Slime::AlkaliJump(VECTOR LkaPos) {
	if (!slimeAttackFlag) {
		return;
	}
	_status = STATUS::ATTACK;
	VECTOR forward{ VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	VECTOR up{ 0.0f,0.1f,0.0f };
	float spd = 2.0f;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim2;
	if (mypH == 1) {
		hitPolyDim2 = MV1CollCheck_Capsule(slimeHandle, 2,
			VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);

		if (hitPolyDim2.HitNum >= 1) {
			lkaHitFlag = true;
		}

		forward = VScale(forward, spd);
		acidcount += 1;
		if (acidcount == 1) {
			slimeDir.y = atan2(lkaPos.z, lkaPos.x);
		}
		if (acidcount <= 40 && acidcount >= 20) {
			slimePos = VAdd(slimePos, VScale(forward, 3.0f));
			slimePos = VAdd(slimePos, VScale(up, 20.0f));
		}
		else if (acidcount > 40 && acidcount != 61) {
			if (sanHitFlag == true) {
				slimePos = VSub(slimePos, VScale(forward, 4.0f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
			else if (sanHitFlag == false) {
				slimePos = VAdd(slimePos, VScale(forward, 0.5f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
			else if (sanHitFlag == false) {
				slimePos = VAdd(slimePos, VScale(forward, 0.5f));
				slimePos = VSub(slimePos, VScale(up, 20.0f));
			}
		}
		else if (acidcount == 61) {
			sanHitFlag == false;
		}
	}
	MV1CollResultPolyDimTerminate(hitPolyDim2);
}

void Slime::AsidWalk(float speed) {
	_status = STATUS::WALK_KAI;

	if (mypH == 1) {
		if (abs(acidPos[asidPassedCount].x - slimePos.x) <= slimeError && abs(acidPos[asidPassedCount].z - slimePos.z) <= slimeError) {
			slimePos = acidPos[asidPassedCount];
			slimeTargetPos = acidPos[asidPassedCount + 1];
			asidPassedCount += 1;
			if (asidPassedCount == 4) {
				slimeTargetPos = acidPos[0];
				asidPassedCount = 0;
			}
		}
		forward = VNorm(VSub(slimeTargetPos, slimePos));
		slimeDir.y = atan2(forward.x * -1, forward.z * -1);
		slimePos = VAdd(slimePos, VScale(forward, speed));
	}
	
}

void Slime::AlkaliWalk(float speed) {
	if (mypH == 2) {
		if (abs(alkaliPos[alkaliPassedCount].x - slimePos.x) <= slimeError && abs(alkaliPos[alkaliPassedCount].z - slimePos.z) <= slimeError) {
			slimePos = alkaliPos[alkaliPassedCount];
			slimeTargetPos = alkaliPos[alkaliPassedCount + 1];
			alkaliPassedCount += 1;
			if (alkaliPassedCount == 4) {
				slimeTargetPos = alkaliPos[0];
				alkaliPassedCount = 0;
			}
		}
		forward = VNorm(VSub(slimeTargetPos, slimePos));
		slimeDir.y = atan2(forward.x * -1, forward.z * -1);
		slimePos = VAdd(slimePos, VScale(forward, speed));
	}
	
}

void Slime::SanTargeting(VECTOR SanPos, float speed) {
	if (mypH == 2) {
		sanPos = VNorm(VSub(SanPos, slimePos));
		sanDistance = VSize(VSub(SanPos, slimePos));
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos = VAdd(slimePos, VScale(sanPos, speed));
		if (sanDistance < 130)
		{
			slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
			_status = STATUS::ATTACK;
			AsidJump(_san->vPos);
		}
	}
}

void Slime::LkaTargeting(VECTOR LkaPos, float speed) {
	if (mypH == 1) {
		lkaPos = VNorm(VSub(LkaPos, slimePos));
		lkaDistance = VSize(VSub(LkaPos, slimePos));
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos = VAdd(slimePos, VScale(lkaPos, speed));
		if (lkaDistance < 130)
		{
			slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
			_status = STATUS::ATTACK;
			AlkaliJump(_lka->vPos);
		}
	}
}
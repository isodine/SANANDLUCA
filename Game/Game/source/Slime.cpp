void Slime::Initialize(float x, float y, float z,int pH) {
	PlayTime = 0.0f;
	slimePos = VGet(x, y, z);
	slimeDir = VGet(0, 0, 0);
	mypH = pH;
	_status = STATUS::NONE;
	AttachAnim = -1;
	slimecount = 0;
	slimeAttackFlag = false;
	slimeSerch = false;
	slimeHitFlag = false;
	//エラーが起きるならここ
	acidPos[0] = { VGet(344, 567, 7105) };
	acidPos[1] = { VGet(140, 567, 7105) };
	acidPos[2] = { VGet(140, 567, 6744) };
	acidPos[3] = { VGet(344, 567, 6744) };
	//acidPos1 = VGet(344, 567, 7105);
	//acidPos2 = VGet(140, 567, 7105);
	//acidPos3 = VGet(140, 567, 6744);
	//acidPos4 = VGet(344, 567, 6744);

	alkaliPos[0] = { VGet(-99, 567, 7105) };
	alkaliPos[1] = { VGet(-303, 567, 7105) };
	alkaliPos[2] = { VGet(-303, 567, 6744) };
	alkaliPos[3] = { VGet(-99, 567, 6744) };
	//alkaliPos1 = VGet(-99, 567, 7105);
	//alkaliPos2 = VGet(-303, 567, 7105);
	//alkaliPos3 = VGet(-303, 567, 6744);
	//alkaliPos4 = VGet(-99, 567, 6744);

	SearchPosMinX = -392;
	SearchPosMaxX = 415;
	SearchPosMinZ = 6647;
	SearchPosMaxZ = 7178;

	MV1SetupCollInfo(slimeHandle, 2, 8, 8, 8);
	slimeHandle = MV1LoadModel("res/slime/slime_multimotion.mv1");
	acidHandle = LoadGraph("res/slime/acidslime_tex.png");
	alkaliHandle = LoadGraph("res/slime/alkalislime_tex.png");

	if (mypH == 1) {
		slimePos = acidPos[0];
		slimeTargetPos = acidPos[1];
	}
	if (mypH == 2) {
		slimePos = alkaliPos[0];
		slimeTargetPos = alkaliPos[1];
	}
}

void Slime::Terminate() {

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
	MV1_COLL_RESULT_POLY_DIM hitPolyDim1;
	MV1_COLL_RESULT_POLY_DIM hitPolyDim2;

	Walk(2.0f);

	hitPolyDim1 = MV1CollCheck_Capsule(slimeHandle, 2,
		VGet(SanPos.x, SanPos.y + 30, SanPos.z), VGet(SanPos.x, SanPos.y + 75, SanPos.z), 30.0f);
	hitPolyDim2 = MV1CollCheck_Capsule(slimeHandle, 2,
		VGet(LkaPos.x, LkaPos.y + 30, LkaPos.z), VGet(LkaPos.x, LkaPos.y + 75, LkaPos.z), 30.0f);

	if (hitPolyDim1.HitNum >= 1 || hitPolyDim2.HitNum >= 1) {
		slimeHitFlag = true;
	}
	else {

	}

	sanDistance = VSize(VSub(SanPos, slimePos));
	lkaDistance = VSize(VSub(LkaPos, slimePos));

	sanPos = VNorm(VSub(SanPos, slimePos));
	lkaPos = VNorm(VSub(LkaPos, slimePos));

	if (sanDistance < 130)
	{
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::ATTACK;
		slimeAttackFlag = true;

	}
	else if (lkaDistance < 130)
	{
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::ATTACK;
		slimeAttackFlag = true;

	}

	else if (sanDistance < lkaDistance && !slimeAttackFlag)
	{          //サンの方が近いときサンを追いかける
		slimeSerch = true;
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::WALK_KAI;

		slimePos = VAdd(slimePos, VScale(forward, speed));
	}
	else if (sanDistance >= lkaDistance && !slimeAttackFlag)
	{
		slimeSerch = false;
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos = VAdd(slimePos, VScale(forward, speed));
	}
	SlimeJump();


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

	MV1CollResultPolyDimTerminate(hitPolyDim1);
	MV1CollResultPolyDimTerminate(hitPolyDim2);
}

void Slime::Render(VECTOR Pos) {
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

//攻撃
void Slime::SlimeJump() {
	if (!slimeAttackFlag) {
		return;
	}

	VECTOR forward{ VTransform({0.0f,0.0f,-1.0f},_rotationMatrix) };
	VECTOR up{ 0.0f,0.1f,0.0f };
	float spd = 2.0f;


	forward = VScale(forward, spd);
	slimecount += 1;
	if (slimeSerch == true && slimecount == 1) {
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
	}
	else if (slimeSerch == false && slimecount == 1) {
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
	}
	if (slimecount <= 20 && slimecount != 0 && slimeAttackFlag == true) {

	}
	else if (slimecount <= 40 && slimecount >= 20 && slimeAttackFlag == true) {
		slimePos = VAdd(slimePos, VScale(forward, 3.0f));
		slimePos = VAdd(slimePos, VScale(up, 20.0f));
	}
	else if (slimecount > 40 && slimecount != 61 && slimeAttackFlag == true) {
		if (slimeHitFlag == true) {
			slimePos = VSub(slimePos, VScale(forward, 4.0f));
			slimePos = VSub(slimePos, VScale(up, 20.0f));
		}
		else if (slimeHitFlag == false) {
			slimePos = VAdd(slimePos, VScale(forward, 0.5f));
			slimePos = VSub(slimePos, VScale(up, 20.0f));
		}

	}
	else if (slimecount == 61) {
		slimecount = 0;
		slimeAttackFlag = false;
		slimeHitFlag = false;
	}
}


void Slime::Walk(float speed) {
	if (mypH == 1) {
		for (auto i = 0; i > 4; i++) {
			if (slimeTargetPos.x == acidPos[i].x && slimeTargetPos.z == acidPos[i].z) {
				forward = VNorm(VSub(slimePos, slimeTargetPos));
				slimePos = VAdd(slimePos, VScale(forward, speed));
				if (slimePos.x == slimeTargetPos.x && slimePos.z == slimeTargetPos.z) {
					slimeTargetPos = acidPos[i + 1];
					if (i == 3) {
						slimeTargetPos = acidPos[0];
					}
				}
			}
		}
	}
	if (mypH == 2) {
		for (auto i = 0; i > 4; i++) {
			if (slimeTargetPos.x == alkaliPos[i].x && slimeTargetPos.z == alkaliPos[i].z) {
				forward = VNorm(VSub(slimePos, slimeTargetPos));
				slimePos = VAdd(slimePos, VScale(forward, speed));
				if (slimePos.x == slimeTargetPos.x && slimePos.z == slimeTargetPos.z) {
					slimeTargetPos = acidPos[i + 1];
					if (i == 3) {
						slimeTargetPos = alkaliPos[0];
					}
				}
			}
		}
	}
	slimeDir.y = atan2(slimeTargetPos.z, slimeTargetPos.x);
	forward = VNorm(VSub(slimePos, slimeTargetPos));
	slimePos = VAdd(slimePos, VScale(forward, speed));
}

void Slime::Targeting(VECTOR SanPos, VECTOR LkaPos, float speed) {
	if (mypH == 1) {
		lkaPos = VNorm(VSub(LkaPos, slimePos));
		lkaDistance = VSize(VSub(LkaPos, slimePos));
		slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos = VAdd(slimePos, VScale(forward, speed));
		if (lkaDistance < 130)
		{
			slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
			_status = STATUS::ATTACK;
			SlimeJump();
		}
	}
	else if (mypH == 2) {
		sanPos = VNorm(VSub(SanPos, slimePos));
		sanDistance = VSize(VSub(SanPos, slimePos));
		slimeDir.y = atan2(sanPos.x * -1, sanPos.z * -1);
		_status = STATUS::WALK_KAI;
		slimePos = VAdd(slimePos, VScale(forward, speed));
		if (lkaDistance < 130)
		{
			slimeDir.y = atan2(lkaPos.x * -1, lkaPos.z * -1);
			_status = STATUS::ATTACK;
			SlimeJump();
		}
	}
}
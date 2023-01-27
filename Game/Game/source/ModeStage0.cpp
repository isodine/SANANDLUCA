#include "AppFrame.h"
//#include "ApplicationMain.h"
#include "ModeStage0.h"
#include "ModeStage1.h"
#include "ModeGameOver.h"

bool ModeStage0::Initialize() {
	if (!base::Initialize()) { return false; }
	handle= MV1LoadModel("res/Balance/Motion/Balance_MOmarge.mv1");
	Mattach_index = MV1AttachAnim(handle, 0, -1, FALSE);
	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	Mtotal_time = MV1GetAttachAnimTotalTime(handle, Mattach_index);
	// �Đ����Ԃ�������
	Mplay_time = 0.0f;
	return true;
}

bool ModeStage0::Terminate() {
	base::Terminate();

	return true;
}

bool ModeStage0::Process() {
	base::Process();

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeStage1(), 1, "stage1");
	}

	if (CheckHitKey(KEY_INPUT_A)) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Add(new ModeGameOver(), 1, "GameOver");
	}


		// �Đ����Ԃ�i�߂�
		Mplay_time += 0.5f;

		if(CheckHitKey(KEY_INPUT_S))
		{
			// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
			if (Mattach_index != -1) {
				MV1DetachAnim(handle, Mattach_index);
				Mattach_index = -1;
			}
			Mattach_index = MV1AttachAnim(handle, 1, -1, FALSE);
		}

		
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		Mtotal_time = MV1GetAttachAnimTotalTime(handle, Mattach_index);


	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (Mplay_time >= Mtotal_time) {
		Mplay_time = 0.0f;
	}

	return true;
}

bool ModeStage0::Render() {

	// 3D��{�ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	//DrawString(0, 0, "�`���[�g���A���X�e�[�W", GetColor(255, 255, 255));
	MV1SetAttachAnimTime(handle, Mattach_index, Mplay_time);
	MV1SetPosition(handle, VGet(500.0f, 500.0f, 0.0f));
	//MV1SetScale(handle, VGet(3.0f, 3.0f, 3.0f));
	MV1DrawModel(handle);

	return true;
}
//#include "AppFrame.h"
//#include "ModeEffekseer.h"
//
//
//bool ModeEffekseer::Initialize() {
//	if (!base::Initialize()) { return false; }
//
//	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
//	// �ǂݍ��ގ��ɑ傫�����w�肷��B
//	_effectResourceHandle = LoadEffekseerEffect("res/san_bomb_1.6/sam_bomb.efkefc_1.6.efkefc", 10.0f);
//
//	return true;
//}
//
//bool ModeEffekseer::Terminate() {
//	base::Terminate();
//
//	// �G�t�F�N�g���\�[�X���폜����B
//	DeleteEffekseerEffect(_effectResourceHandle);
//
//
//	return true;
//}
//
//bool ModeEffekseer::Process() {
//	base::Process();
//	int keya = Key;
//	Key = GetJoypadInputState(DX_INPUT_KEY);
//	Trg = (Key ^ keya) & Key;	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
//
//
//	// ESC�L�[�ŕ���
//	bool close = false;
//	if (Trg & PAD_INPUT_9) {
//		close = true;
//	}
//
//	// ���[�h�J�E���^���g����60fps�ŃG�t�F�N�g�𐶐�
//	if (GetModeCount() % 60 == 0) {
//		// �G�t�F�N�g���Đ�����B
//		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
//
//		// �G�t�F�N�g�̈ʒu�����Z�b�g����B
//		_position_x = 0.0f;
//	}
//
//	// �Đ����̃G�t�F�N�g���ړ�����B
//	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, 50.f, 0);
//	_position_x += 0.2f;
//
//	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
//	UpdateEffekseer3D();
//
//
//	// ����
//	if (close) {
//		// ���̃��[�h���폜����
//		ModeServer::GetInstance()->Del(this);
//	}
//
//
//
//	return true;
//}
//
//bool ModeEffekseer::Render() {
//	base::Render();
//
//	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
//	Effekseer_Sync3DSetting();
//
//	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
//	DrawEffekseer3D();
//
//
//	return true;
//}
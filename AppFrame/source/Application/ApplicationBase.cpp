
#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {
	GameEnd = false;

	// DXライブラリの初期化
	if(AppWindowed()){
		ChangeWindowMode(true);							// ウィンドウモードに指定する
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// ただし、DirectX11を使用する場合は実行する必要はない。
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();


	// 乱数初期化
	srand((unsigned int)time(NULL));

	// モードサーバの初期化
	_serverMode = new ModeServer();
	//DxSetAllocPrintFlag(1);// ＤＸライブラリ内でメモリ確保が行われる時に情報を出力するかどうかをセットする

	return true;
}

bool ApplicationBase::Terminate() {

	// Effekseerを終了する。
	Effkseer_End();

	// 音をすべて削除します
	InitSoundMem();

	// すべてのモデルを削除する
	MV1InitModel();

	// DXライブラリ開放
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// キーの入力、トリガ入力を得る
	int keyold1P = _gKey1P;
	_gKey1P = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg1P = (_gKey1P ^ keyold1P) & _gKey1P;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	int keyold2P = _gKey2P;
	_gKey2P = GetJoypadInputState(DX_INPUT_PAD2);
	_gTrg2P = (_gKey2P ^ keyold2P) & _gKey2P;	// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
	//int keyoldEf = _gTrgEf;
	//_gKeyEf = GetJoypadInputState(DX_INPUT_KEY);
	//_gTrgEf = (_gKeyEf ^ keyoldEf) & _gKeyEf;

	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	return true;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}

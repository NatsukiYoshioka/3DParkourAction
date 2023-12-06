#include"FpsControl.h"
#include"Load.h"
#include"GameManager.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"

//WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//--------------------------------------//
	//初期設定
	//--------------------------------------//
	//DxLib初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetWaitVSyncFlag(0);		//垂直同期を切る

	//画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	FpsControl::CreateInstance();
	auto fpsControl = FpsControl::GetInstance();

	PadInput::CreateInstance();

	GameManager::CreateInstance();
	auto gameManager = GameManager::GetInstance();

	//--------------------------------------//
	//メインループ
	//--------------------------------------//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//フレームレート計算
		fpsControl->Update();

		//ゲームの更新
		gameManager->Update();

		//ゲームの描画
		gameManager->Draw();

		//フレームレート表示
		fpsControl->Draw();

		//フレームレート制御
		fpsControl->Control();

		ScreenFlip();
	}

	//クラスの後処理
	FpsControl::DestroyInstance();
	GameManager::DestroyInstance();
	PadInput::DestroyInstance();

	//DXライブラリの後始末
	DxLib_End();

	//ソフトの終了
	return 0;
}
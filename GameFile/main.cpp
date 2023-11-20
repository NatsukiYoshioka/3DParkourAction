#include"FpsControl.h"
#include"Load.h"
#include"GameObjectManager.h"
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

	FpsControl::CreateInstance();
	auto fpsControl = FpsControl::GetInstance();

	//--------------------------------------//
	//メインループ
	//--------------------------------------//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//フレームレート計算
		fpsControl->Update();



		//フレームレート表示
		fpsControl->Draw();

		//フレームレート制御
		fpsControl->Control();

		ScreenFlip();
	}

	FpsControl::DestroyInstance();

	//DXライブラリの後始末
	DxLib_End();

	//ソフトの終了
	return 0;
}
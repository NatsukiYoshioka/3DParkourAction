#include"common.h"
#include<cmath>
#include"DxLib.h"
#include "FpsControl.h"

FpsControl* FpsControl::fpsControl = nullptr;
const unsigned int FpsControl::blueColor = GetColor(255, 255, 0);

//カウントの初期化
FpsControl::FpsControl() :count(initializeNum), nowFps(initializeNum)
{
	startTime = GetNowCount();
}

//インスタンスが一度も生成されていなかったら生成する
void FpsControl::CreateInstance()
{
	if (!fpsControl)
	{
		fpsControl = new FpsControl();
	}
}

//インスタンスが生成されていたら破棄する
void FpsControl::DestroyInstance()
{
	if (fpsControl)
	{
		delete(fpsControl);
	}
}

//フレームレート制御
void FpsControl::Update()
{
	if (count == initializeNum)
	{
		//1フレーム目なら時刻を記憶
		startTime = GetNowCount();
	}
	if (count == sampleAvg)
	{
		//60フレーム目なら平均を計算する
		int t = GetNowCount();
		nowFps = secondFrame / ((t - startTime) / (float)sampleAvg);
		count = initializeNum;
		startTime = t;
	}
	count++;
}

//FPS表示
void FpsControl::Draw()
{
	DrawFormatString(fpsX, fpsY, blueColor, valueString, nowFps);
}

//フレームレートを60で固定する
void FpsControl::Control()
{
	int tookTime = GetNowCount() - startTime;			//かかった時間
	int waitTime = count * static_cast<int>(secondFrame) / FPS - tookTime;		//待つべき時間

	if (waitTime > initializeNum)
	{
		Sleep(waitTime);	//待機
	}
}
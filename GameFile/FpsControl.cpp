#include"common.h"
#include<cmath>
#include"DxLib.h"
#include "FpsControl.h"

FpsControl* FpsControl::fpsControl = nullptr;
const unsigned int FpsControl::blueColor = GetColor(255, 255, 0);

//�J�E���g�̏�����
FpsControl::FpsControl() :count(initializeNum), nowFps(initializeNum)
{
	startTime = GetNowCount();
}

//�C���X�^���X����x����������Ă��Ȃ������琶������
void FpsControl::CreateInstance()
{
	if (!fpsControl)
	{
		fpsControl = new FpsControl();
	}
}

//�C���X�^���X����������Ă�����j������
void FpsControl::DestroyInstance()
{
	if (fpsControl)
	{
		delete(fpsControl);
	}
}

//�t���[�����[�g����
void FpsControl::Update()
{
	if (count == initializeNum)
	{
		//1�t���[���ڂȂ玞�����L��
		startTime = GetNowCount();
	}
	if (count == sampleAvg)
	{
		//60�t���[���ڂȂ畽�ς��v�Z����
		int t = GetNowCount();
		nowFps = secondFrame / ((t - startTime) / (float)sampleAvg);
		count = initializeNum;
		startTime = t;
	}
	count++;
}

//FPS�\��
void FpsControl::Draw()
{
	DrawFormatString(fpsX, fpsY, blueColor, valueString, nowFps);
}

//�t���[�����[�g��60�ŌŒ肷��
void FpsControl::Control()
{
	int tookTime = GetNowCount() - startTime;			//������������
	int waitTime = count * static_cast<int>(secondFrame) / FPS - tookTime;		//�҂ׂ�����

	if (waitTime > initializeNum)
	{
		Sleep(waitTime);	//�ҋ@
	}
}
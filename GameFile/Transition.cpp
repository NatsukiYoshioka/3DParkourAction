#include"common.h"
#include"DxLib.h"
#include "Transition.h"

Transition* Transition::transition = nullptr;
float Transition::whiteTransRate = static_cast<float>(initializeNum);
float Transition::blackTransRate = static_cast<float>(initializeNum);

//�摜�̃��[�h
Transition::Transition()
{
	whiteTextureHandle = LoadGraph(whiteTexturePath);
	blackTextureHandle = LoadGraph(blackTexturePath);
}

//�f�[�^�j��
Transition::~Transition()
{
	if (whiteTextureHandle != noHandle)DeleteGraph(whiteTextureHandle);
	if (blackTextureHandle != noHandle)DeleteGraph(blackTextureHandle);
}

//�C���X�^���X����
void Transition::CreateInstance()
{
	if (!transition)
	{
		transition = new Transition();
	}
}

//�C���X�^���X�j��
void Transition::DestroyInstance()
{
	if (transition)
	{
		delete(transition);
	}
}

//���摜�̓��ߗ��ݒ�
void Transition::UpdateWhiteTransition(float transRate)
{
	whiteTransRate = transRate;
	if (whiteTransRate >= maxTransRate)
	{
		whiteTransRate = maxTransRate;
	}
	if (whiteTransRate <= static_cast<float>(initializeNum))
	{
		whiteTransRate = static_cast<float>(initializeNum);
	}
}

//���摜�̓��ߗ��ݒ�
void Transition::UpdateBlackTransition(float transRate)
{
	blackTransRate = transRate;
	if (blackTransRate >= maxTransRate)
	{
		blackTransRate = maxTransRate;
	}
	if (blackTransRate <= static_cast<float>(initializeNum))
	{
		blackTransRate = static_cast<float>(initializeNum);
	}
}

//�摜�̕`��
void Transition::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(maxFade * whiteTransRate));
	DrawExtendGraph(texturePosX1, texturePosY1, texturePosX2, texturePosY2, whiteTextureHandle, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, initializeNum);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(maxFade * blackTransRate));
	DrawExtendGraph(texturePosX1, texturePosY1, texturePosX2, texturePosY2, blackTextureHandle, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, initializeNum);
}
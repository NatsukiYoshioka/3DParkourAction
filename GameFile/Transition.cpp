#include"common.h"
#include"DxLib.h"
#include "Transition.h"

Transition* Transition::transition = nullptr;
float Transition::whiteTransRate = static_cast<float>(initializeNum);
float Transition::blackTransRate = static_cast<float>(initializeNum);

//画像のロード
Transition::Transition()
{
	whiteTextureHandle = LoadGraph(whiteTexturePath);
	blackTextureHandle = LoadGraph(blackTexturePath);
}

//データ破棄
Transition::~Transition()
{
	if (whiteTextureHandle != noHandle)DeleteGraph(whiteTextureHandle);
	if (blackTextureHandle != noHandle)DeleteGraph(blackTextureHandle);
}

//インスタンス生成
void Transition::CreateInstance()
{
	if (!transition)
	{
		transition = new Transition();
	}
}

//インスタンス破棄
void Transition::DestroyInstance()
{
	if (transition)
	{
		delete(transition);
	}
}

//白画像の透過率設定
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

//黒画像の透過率設定
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

//画像の描画
void Transition::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(maxFade * whiteTransRate));
	DrawExtendGraph(texturePosX1, texturePosY1, texturePosX2, texturePosY2, whiteTextureHandle, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, initializeNum);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(maxFade * blackTransRate));
	DrawExtendGraph(texturePosX1, texturePosY1, texturePosX2, texturePosY2, blackTextureHandle, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, initializeNum);
}
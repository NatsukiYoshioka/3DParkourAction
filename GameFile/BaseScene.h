#pragma once
#include<DxLib.h>

static const int stringX = 0;
static const int stringY = 16;
static const unsigned int sceneStringColor = GetColor(255, 255, 255);

/// <summary>
/// すべてのシーンの基底クラス
/// </summary>
class BaseScene
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
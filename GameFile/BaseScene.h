#pragma once

/// <summary>
/// すべてのシーンの基底クラス
/// </summary>
class BaseScene
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
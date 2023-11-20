#pragma once
#include"DxLib.h"

/// <summary>
/// 全てのゲームオブジェクトの基底クラス
/// </summary>
class GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameObject();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameObject();

	//純粋仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;
protected:
	int modelHandle;			//モデルのハンドル
	VECTOR pos;					//オブジェクトの座標
};


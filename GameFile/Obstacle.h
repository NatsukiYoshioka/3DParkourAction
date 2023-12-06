#pragma once
#include"ObjectTag.h"
#include<DxLib.h>

class GameObject;

/// <summary>
/// 障害物オブジェクトクラス
/// </summary>
class Obstacle:public GameObject
{
public:
	/// <summary>
	/// モデルの取得と座標の初期化
	/// </summary>
	/// <param name="modelHandle">モデルハンドル</param>
	/// <param name="pos">オブジェクトの座標</param>
	Obstacle(int modelHandle, VECTOR pos);

	/// <summary>
	/// データの解放
	/// </summary>
	~Obstacle();

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void Update();

	/// <summary>
	/// オブジェクトの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// モデルハンドル取得
	/// </summary>
	/// <returns>モデルハンドル</returns>
	int GetModelHandle() { return modelHandle; }

	/// <summary>
	/// オブジェクトタグ取得
	/// </summary>
	/// <returns>オブジェクトタグ</returns>
	ObjectTag GetObjectTag() { return tag; }

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <returns>オブジェクトの座標</returns>
	VECTOR GetPos() { return pos; }

private:
	
};


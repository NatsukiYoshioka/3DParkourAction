#pragma once
#include"ObjectTag.h"
#include<DxLib.h>

class GameObject;

/// <summary>
/// フィールドオブジェクトクラス
/// </summary>
class Field:public GameObject
{
public:
	/// <summary>
	/// モデルの取得と座標と角度の初期化
	/// </summary>
	/// <param name="modelHandle">モデルハンドル</param>
	/// <param name="pos">オブジェクトの座標</param>
	Field(int modelHandle, VECTOR pos,float angle);

	/// <summary>
	/// データの解放
	/// </summary>
	~Field();

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void Update(GameManager::SCENE nowScene);

	/// <summary>
	/// オブジェクトの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// モデルハンドルの取得
	/// </summary>
	/// <returns>モデルハンドル</returns>
	int GetModelHandle() { return modelHandle; }

	/// <summary>
	/// オブジェクトのタグ取得
	/// </summary>
	/// <returns>オブジェクトタグ</returns>
	ObjectTag GetObjectTag() { return tag; }

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <returns>オブジェクトの座標</returns>
	VECTOR GetPos() { return pos; }

private:
	VECTOR angle;		//モデルの角度

	static constexpr int frameIndex = -1;		//モデルのフレームの番号
	static constexpr int collisionDivNum = 8;	//当たり判定分割数
};


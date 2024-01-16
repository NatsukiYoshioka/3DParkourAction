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
	/// オブジェクトの生成
	/// </summary>
	/// <param name="modelHandle">モデルハンドル</param>
	/// <param name="pos">オブジェクトの座標</param>
	/// <param name="angle">オブジェクトの角度</param>
	/// <param name="isSlide">くぐれるかどうか</param>
	Obstacle(int modelHandle, VECTOR pos, float angle, int isSlide);

	/// <summary>
	/// データの解放
	/// </summary>
	~Obstacle();

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void Update(GameManager::SCENE nowScene);

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
	VECTOR angle;

	static const VECTOR scale;				//モデルのスケール

	static constexpr int frameIndex = -1;		//モデルのフレームの番号
	static constexpr int collisionDivNum = 2;	//当たり判定分割数
};


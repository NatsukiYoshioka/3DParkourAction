#pragma once
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
	void Update();

	/// <summary>
	/// オブジェクトの描画
	/// </summary>
	void Draw();

private:
	VECTOR angle;

	static constexpr int frameIndex = -1;
	static constexpr int collisionDivNum = 10;
};


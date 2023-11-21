#pragma once
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

private:
	
};


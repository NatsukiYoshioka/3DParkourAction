#pragma once
#include<DxLib.h>

class GameOnject;

class Camera:public GameObject
{
public:
	/// <summary>
	/// 
	/// </summary>
	Camera();

	/// <summary>
	/// データの解放
	/// </summary>
	~Camera();

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void Update();

	void Draw(){}

	/// <summary>
	/// オブジェクトの座標の取得
	/// </summary>
	/// <returns></returns>
	VECTOR GetPos() { return pos; }
};


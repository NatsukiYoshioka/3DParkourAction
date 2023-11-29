#pragma once
#include<DxLib.h>

class GameOnject;

/// <summary>
/// カメラの制御クラス
/// </summary>
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
};


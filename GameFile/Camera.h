#pragma once
#include<DxLib.h>

class GameOnject;
class PadInput;

/// <summary>
/// カメラの制御クラス
/// </summary>
class Camera:public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
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

	/// <summary>
	/// 入力処理更新
	/// </summary>
	void UpdateInput();

	void Draw(){}

private:
	PadInput* input;		//コントローラー入力情報管理クラス
	float rotateV;			//カメラX軸回転量

	static constexpr float directionSpeed = 0.05f;		//方向転換速度
};


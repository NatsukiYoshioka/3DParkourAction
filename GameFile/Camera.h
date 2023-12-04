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
	VECTOR angle;			//カメラの向き
	VECTOR addPos;			//カメラの位置加算量

	float rotateV;			//カメラX軸回転量

	static constexpr float fixPosY = 12.5f;				//カメラY座標調整量
	static constexpr float fixFoewardPos = 12.5f;		//カメラ前押し出し量

	static constexpr float directionSpeed = 0.05f;						//方向転換速度
	static constexpr float maxUpDirection = -90.0f * DX_PI_F / 180.0f;	//カメラの上方向限度
	static constexpr float maxDownDirection = 60.0f * DX_PI_F / 180.0f;	//カメラの下方向限度

	static constexpr float cameraNear = 2.5f;			//カメラの手前描画範囲
	static constexpr float cameraFar = 20000.0f;		//カメラの奥描画距離
};


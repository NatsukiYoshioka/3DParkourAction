#pragma once
#include"ObjectTag.h"
#include"common.h"
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
	void Update(GameManager::SCENE nowScene);

	/// <summary>
	/// 入力処理更新
	/// </summary>
	void UpdateInput();

	void Draw(){}

	/// <summary>
	/// モデルハンドル取得
	/// </summary>
	/// <returns>モデルハンドル</returns>
	int GetModelHandle() { return initializeNum; }

	/// <summary>
	/// タグの取得
	/// </summary>
	/// <returns>オブジェクトタグ</returns>
	ObjectTag GetObjectTag() { return tag; }

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>オブジェクトの座標</returns>
	VECTOR GetPos() { return pos; }

private:
	PadInput* input;		//コントローラー入力情報管理クラス
	VECTOR angle;			//カメラの向き
	VECTOR addPos;			//カメラの位置加算量

	float forwardPos;		//カメラ前押し出し量
	float rotateV;			//カメラX軸回転量
	float fov;				//視野角

	static constexpr float fixPosY = 5.0f;				//カメラY座標調整量
	static constexpr float fixForwardPos = 7.5f;		//カメラ前押し出し量限界値
	static constexpr float firstForwardPos = -30.5f;	//カメラの初期押し出し量
	//static constexpr float fixForwardPos = -120.5f;	//アニメーションデバッグ用

	static constexpr float directionSpeed = 0.025f;						//方向転換速度
	static constexpr float maxUpDirection = -90.0f * DX_PI_F / 180.0f;	//カメラの上方向限度
	static constexpr float maxDownDirection = 70.0f * DX_PI_F / 180.0f;	//カメラの下方向限度

	static constexpr float cameraNear = 0.5f;			//カメラの手前描画範囲
	static constexpr float cameraFar = 8000.0f;		//カメラの奥描画距離

	static constexpr float initializeFov = 90.0f;
};


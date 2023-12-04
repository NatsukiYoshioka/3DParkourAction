#pragma once
#include<vector>
#include<DxLib.h>

using namespace std;

class GameObject;
class PadInput;

class Player :public GameObject
{
public:
	/// <summary>
	/// プレイヤーの状態
	/// </summary>
	enum class STATUS
	{
		CROUCHED_TO_STAND,			//立ち上がる
		CROUCH,						//しゃがむ
		DEAD_FALL,					//落下
		FALL,						//降りる
		FALLING_TO_ROLL,			//前転着地
		JUMP,						//ジャンプ
		JUMP_OVER,					//飛び越える
		LAND,						//着地
		LEFT_WALLRUN,				//左壁ウォールラン
		RIGHT_WALLRUN,				//右壁ウォールラン
		RUN,						//走る
		SLIDE,						//スライディング
		STAND,						//立つ
		CROUNSHING_WALK,			//しゃがみ歩き
		STANDING_TO_CROUCH,			//立ちからしゃがむ
		RUN_BACK,					//後ろ走り
		RUN_RIGHT,					//右走り
		RUN_LEFT					//左走り
	};

	/// <summary>
	/// オブジェクトの初期化
	/// </summary>
	/// <param name="modelHandle">モデルハンドル</param>
	/// <param name="animationHandle">アニメーションハンドルのvector配列</param>
	Player(int modelHandle, vector<int> animationHandle);

	/// <summary>
	/// データの解放
	/// </summary>
	~Player();

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void Update();

	/// <summary>
	/// 入力による挙動の更新
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// アニメーションの更新
	/// </summary>
	void UpdateAnimation();

	/// <summary>
	/// オブジェクトの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// オブジェクトの座標の取得
	/// </summary>
	/// <returns></returns>
	static VECTOR GetHeadPos() { return headPos; }

	/// <summary>
	/// プレイヤーの向きを取得
	/// </summary>
	/// <returns>プレイヤーの向き</returns>
	static VECTOR GetAngle() { return angle; }

private:
	vector<int> animationHandle;		//アニメーションの配列
	STATUS status;						//プレイヤーの状態

	PadInput* input;					//コントローラー入力管理クラスのアドレス

	static const VECTOR scale;

	VECTOR addMove;									//プレイヤーの移動加算値
	static constexpr float moveSpeed = 4.0f;		//プレイヤーの移動速度移動速度

	static VECTOR angle;							//プレイヤーの向き
	static constexpr float directionSpeed = 0.1f;	//プレイヤーの方向転換速度

	static const VECTOR fixAngle;				//モデルの方向修正

	float totalAnimTime;				//アニメーションの総再生時間
	float playAnimTime;							//アニメーションの再生時間

	static VECTOR headPos;						//頭のフレームの座標
	static constexpr int headFrameIndex = 5;	//頭のフレームの番号
};


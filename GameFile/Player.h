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
		STANDING_TO_CROUCH			//立ちからしゃがむ
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
	/// オブジェクトの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// オブジェクトの座標の取得
	/// </summary>
	/// <returns></returns>
	static VECTOR GetHeadPos() { return headPos; }

private:
	vector<int> animationHandle;		//アニメーションの配列
	STATUS status;						//プレイヤーの状態

	PadInput* input;					//コントローラー入力管理クラスのアドレス

	static constexpr float moveSpeed = 1.0f;	//プレイヤーの移動速度移動速度

	static VECTOR headPos;						//頭のフレームの座標
	static constexpr int headFrameIndex = 5;	//頭のフレームの番号
};


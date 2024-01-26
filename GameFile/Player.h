#pragma once
#include"ObjectTag.h"
#include"common.h"
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
	/// オブジェクトの初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void Update();

	/// <summary>
	/// チュートリアル処理更新
	/// </summary>
	void UpdateTutorial();

	/// <summary>
	/// 入力による挙動の更新
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// デバッグ用移動処理
	/// </summary>
	void DebugInput();

	/// <summary>
	/// ワールド座標左移動計算関数
	/// </summary>
	/// <param name="vec">加算するベクトル</param>
	/// <returns>加算するベクトル</returns>
	VECTOR CalcLeftMove(VECTOR vec);

	/// <summary>
	/// ワールド座標右移動計算関数
	/// </summary>
	/// <param name="vec">加算するベクトル</param>
	/// <returns>加算するベクトル</returns>
	VECTOR CalcRightMove(VECTOR vec);

	/// <summary>
	/// ワールド座標前移動計算関数
	/// </summary>
	/// <param name="vec">加算するベクトル</param>
	/// <returns>加算するベクトル</returns>
	VECTOR CalcFrontMove(VECTOR vec);

	/// <summary>
	/// ワールド座標後ろ移動計算関数
	/// </summary>
	/// <param name="vec">加算するベクトル</param>
	/// <returns>加算するベクトル</returns>
	VECTOR CalcBehindMove(VECTOR vec);

	/// <summary>
	/// 重力処理の更新
	/// </summary>
	void UpdateGravity();

	/// <summary>
	/// アニメーションの更新
	/// </summary>
	void UpdateAnimation();

	/// <summary>
	/// ライトの更新
	/// </summary>
	void UpdateLight();

	/// <summary>
	/// リスポーン処理
	/// </summary>
	void Respone();

	/// <summary>
	/// 当たり判定線分の計算
	/// </summary>
	void CalcCollisionLine();

	/// <summary>
	/// 他のオブジェクトとの当たり判定
	/// </summary>
	/// <param name="other">他オブジェクト</param>
	void OnCollisionEnter(GameObject* other,const ObjectTag tag)override;

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

	/// <summary>
	/// モデルハンドル取得
	/// </summary>
	/// <returns>モデルハンドル</returns>
	int GetModelHandle() { return initializeNum; }

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
	bool debug;							//デバッグ中かどうか
	bool isInit;                        //オブジェクトを初期化したかどうか
	bool isStart;						//ゲームがスタートしたかどうか
	vector<int> animationHandle;		//アニメーションの配列
	STATUS status;						//プレイヤーの状態

	static const VECTOR initPos;		//初期座標
	static const VECTOR tutorialPos;	//チュートリアルを始める時の座標
	VECTOR restartPos;					//リスポーンする座標
	static constexpr float restartHeight = 100.0f;	//リスポーンする高さ

	PadInput* input;					//コントローラー入力管理クラスのアドレス

	static const VECTOR scale;			//モデルのスケール

	static const unsigned int debugColor;			//当たり判定カプセルのカラー

	int forwardLightHandle;								//前を照らすライトハンドル
	int downLightHandle;								//地面を照らすライトハンドル
	VECTOR lightDirection;								//ライトの向き
	static const VECTOR downLightDirection;				//地面を照らすライトの向き
	static constexpr float downLightHeight = 10000.0f;	//地面を照らすライトの高さ

	VECTOR addMove;									//プレイヤーの移動加算値
	VECTOR moveDirection;							//プレイヤーの向くべき方向
	VECTOR moveDirectionX;							//プレイヤーのローカルX軸で進むべき方向
	VECTOR moveDirectionZ;							//プレイヤーのローカルZ軸で進むべき方向
	int isHitWall;									//壁に当たったかどうか
	bool isLeft;									//左の壁に当たったかどうか
	float moveSpeed;								//プレイヤーの移動速度移動速度
	static constexpr float initializeSpeed = 2.0f;	//プレイヤーの初速

	bool isGround;									//地面に立っているか
	bool isJump;									//ジャンプしたかどうか
	bool isMove;									//動いているか
	bool isWallRun;									//ウォールランしているかどうか
	bool isWallJump;								//壁ジャンプしたかどうか
	bool isSlide;									//スライディングしているかどうか
	bool isStandByToJumpOver;						//飛び越え待機しているかどうか
	bool isStandByToBigJump;						//大ジャンプ待機しているかどうか

	float gravity;									//プレイヤーにかかる重力量
	static constexpr float addGravity = 0.1f;		//重力加算量
	static constexpr float maxGravity = 3.0f;		//最大重力量

	float jump;										//ジャンプ力
	static constexpr float jumpPower = 4.5f;		//ジャンプ力加算量
	static constexpr float bigJumpPower = 9.0f;		//大ジャンプ加算量

	static VECTOR angle;							//プレイヤーの向き
	VECTOR jumpAngle;								//ジャンプしたときの向き
	static constexpr float directionSpeed = 0.05f;	//プレイヤーの方向転換速度

	static constexpr float jumpOverDistance = 30.0f;	//障害物飛び越えができる距離
	static constexpr float fixPosYToJumpOver = 10.0f;	//障害物飛び越え時のY座標調整量
	VECTOR fixJumpOverPos;								//障害物飛び越え時の移動修正量

	VECTOR fixSlidePos;								//スライディングするときの移動修正量
	static constexpr float slideSpeed = 1.0f;		//スライディングするときの移動速度

	static const VECTOR fixAngle;				//モデルの方向修正

	int animationIndex;								//アニメーション番号
	float totalAnimTime;							//アニメーションの総再生時間
	float playAnimTime;								//アニメーションの再生時間
	static constexpr float animationSpeed = 1.0f;	//アニメーション再生速度

	static VECTOR headPos;							//頭のフレームの座標
	static constexpr int headFrameIndex = 5;		//頭のフレームの番号
	VECTOR spinePos;								//腰の座標
	static constexpr int spineFrameIndex = 2;		//腰のフレーム番号

	static constexpr int lineNum = 2;				//線分の2点
	static constexpr int lineDivNum = 5;			//当たり判定用線分の列数

	static constexpr float groundLineWidth = 5.0f;		//地面当たり判定線分の長さ
	static constexpr float groundLineSpace = 0.75f;		//地面当たり判定線分の間隔

	VECTOR groundLinePos[lineDivNum][lineDivNum];			//地面の当たり判定用線分の座標

	static constexpr float wallCollisionLineWidth = 8.0f;	//壁の当たり判定線分の長さ
	static constexpr float wallCollisionLineSpace = 8.0f;	//壁の当たり判定線分の感覚
	static constexpr float fixWallCollisionLinePosY = 12.0f;	//壁の当たり判定線分のY座標調整量

	VECTOR wallCollisionLinePos[lineNum][lineDivNum][lineDivNum];	//壁との当たり判定用線分の座標
	VECTOR sideCollisionLinePos[lineNum][lineDivNum][lineDivNum];	//側面の当たり判定用線分の座標

	static const VECTOR crossCollisionLine;			//当たり判定線分の外積計算用変数

	static const VECTOR transformWallCollisionLine;			//壁当たり判定のベクトル変換用変数
	static const VECTOR transformReverseWallCollisionLine;	//壁当たり判定の逆方向ベクトル変換用変数

	static constexpr int jumpButtonIndex = 12;		//ジャンプボタンの番号
	static constexpr int slideButtonIndex = 13;		//スライディングボタンの番号

	static constexpr int debugSpeed = 2;			//デバッグ時の移動スピード

	static constexpr float goalX = 50.0f;         //ゴール座標
};


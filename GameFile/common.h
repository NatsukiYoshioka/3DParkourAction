#pragma once
#include"DxLib.h"

const auto SCREEN_WIDTH = 1920;			  //スクリーンの横サイズ;
const auto SCREEN_HEIGHT = 1080;          //スクリーンの縦サイズ;
const auto SCREEN_COLOR = 16;	          //スクリーンカラー;

static const int bipartition = 2;

static const int noHandle = -1;			//ハンドルが適用されていない場合の定数
static const int        initializeNum = 0;          //初期化定数
static const float      secondFrame = 1000.0f;      //秒間フレーム数

static const VECTOR initializePos = VGet(0.0f, 0.0f, 0.0f);		//座標初期化定数

static const float pi1_f = 180.0f;		//ラジアン計算用定数

static const VECTOR transformVector = VGet(0.0f, 0.0f, 0.1f);			//行列からベクトル変換用変数
static const VECTOR transformReverseVector = VGet(0.0f, 0.0f, -0.1f);	//行列→ベクトル変換逆方向
static const VECTOR crossVector = VGet(0.0f, 1.0f, 0.0f);		//外積計算用ベクトル

static constexpr float sceneTransitionTime = 45.0f;			//シーン遷移時間
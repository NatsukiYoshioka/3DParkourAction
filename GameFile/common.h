#pragma once
#include"DxLib.h"

constexpr auto SCREEN_WIDTH = 1920;			  //スクリーンの横サイズ;
constexpr auto SCREEN_HEIGHT = 1080;          //スクリーンの縦サイズ;
constexpr auto SCREEN_COLOR = 16;	          //スクリーンカラー;

static constexpr int        initializeNum = 0;          //初期化定数
static constexpr float      secondFrame = 1000.0f;      //秒間フレーム数

static const VECTOR initializePos = VGet(0.0f, 0.0f, 0.0f);
#pragma once
#include<DxLib.h>
#include"ObjectTag.h"

class GameObject;

/// <summary>
/// UIオブジェクト管理クラス
/// </summary>
class UI:public GameObject
{
public:
    /// <summary>
    /// ハンドルと座標の初期化
    /// </summary>
    /// <param name="textureHandle">テクスチャハンドル</param>
    /// <param name="pos">テクスチャの座標</param>
    UI(int textureHandle, VECTOR pos,int drawTiming);

    /// <summary>
    /// データの解放
    /// </summary>
    ~UI();

    /// <summary>
    /// オブジェクトの更新
    /// </summary>
    void Update();

    /// <summary>
    /// オブジェクトの描画
    /// </summary>
    void Draw();

    /// <summary>
    /// テクスチャハンドルの取得
    /// </summary>
    /// <returns>テクスチャハンドル</returns>
    int GetModelHandle() { return modelHandle; }

    /// <summary>
    /// オブジェクトのタグ取得
    /// </summary>
    /// <returns>オブジェクトタグ</returns>
    ObjectTag GetObjectTag() { return tag; }

    /// <summary>
    /// オブジェクトの座標取得
    /// </summary>
    /// <returns>オブジェクト座標</returns>
    VECTOR GetPos() { return pos; }

private:
    int drawTiming;

    static constexpr int titleIndex = 0;            //タイトルに描画するUIの番号
    static constexpr int inGameIndex = 1;           //ゲーム中に描画するUIの番号
    static constexpr int resultIndex = 2;           //リザルトに描画するUIの番号

    static constexpr int cursorIndex = 1;           //カーソルのUI番号
    static constexpr int titleUIIndex = 2;          //タイトル用UI番号

    //モード選択時のカーソルのX座標
    static constexpr float playCursorX = 350.0f;
    static constexpr float tutorialCursorX = 800.0f;
    static constexpr float exitCursorX = 1250.0f;

    //UIのサイズ
    float sizeX;
    float sizeY;

    float dimSize;                                     //UIの縮小サイズ
    static constexpr float titleLength = 1.75f;        //タイトルUIの幅

    float cursorAngle;                                 //カーソルの回転角度

    static constexpr float rotationSpeed = 0.001f;     //カーソルの回転速度
    static const float maxAngle;                       //カーソルの最大角度

    static constexpr float defaultDimSize = 2.5f;      //通常のUI縮小量
    static constexpr float cursorDimSize = 2.0f;       //カーソルのUI縮小量
    static constexpr float cursorScale = 0.1f;         //カーソルのスケール
};


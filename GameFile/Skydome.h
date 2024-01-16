#pragma once
#include"ObjectTag.h"
#include"common.h"
#include<DxLib.h>

class GameObject;

/// <summary>
/// スカイドームの制御クラス
/// </summary>
class Skydome:public GameObject
{
public:
    /// <summary>
    /// スカイドームの初期化
    /// </summary>
    /// <param name="modelHandle">モデルハンドル</param>
    Skydome(int modelHandle);

    /// <summary>
    /// データの開放
    /// </summary>
    ~Skydome();

    /// <summary>
    /// スカイドームの更新
    /// </summary>
    void Update(GameManager::SCENE nowScene);

    /// <summary>
    /// スカイドームの描画
    /// </summary>
    void Draw();

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
    static const VECTOR scale;              //スカイドームの大きさ
    static constexpr float height = 350.0f; //スカイドームの高さ
};


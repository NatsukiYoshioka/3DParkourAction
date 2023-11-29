#pragma once
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
    void Update();

    /// <summary>
    /// スカイドームの描画
    /// </summary>
    void Draw();
};


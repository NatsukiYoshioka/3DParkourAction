#pragma once
#include<DxLib.h>

/// <summary>
/// コントローラー入力制御クラス
/// </summary>
class PadInput
{
private:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PadInput();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PadInput(){}

public:
    /// <summary>
    /// インスタンス生成
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// インスタンス破棄
    /// </summary>
    static void DestroyInstance();

    /// <summary>
    /// インスタンス取得
    /// </summary>
    /// <returns>クラスのインスタンス</returns>
    static PadInput* GetInstance() { return padInput; }

    /// <summary>
    /// コントローラー入力情報の更新
    /// </summary>
    void Update();

    /// <summary>
    /// コントローラー入力情報の取得
    /// </summary>
    /// <returns>コントローラー入力情報</returns>
    XINPUT_STATE GetInput() { return input; }
private:
    static PadInput* padInput;      //クラスインスタンス
    XINPUT_STATE input;             //コントローラー入力情報
};

static const int buttonA = 12;

// XInputボタン入力定義
//#define XINPUT_BUTTON_DPAD_UP		(0)	→ デジタル方向ボタン上
//#define XINPUT_BUTTON_DPAD_DOWN		(1)	→ デジタル方向ボタン下
//#define XINPUT_BUTTON_DPAD_LEFT		(2)	→ デジタル方向ボタン左
//#define XINPUT_BUTTON_DPAD_RIGHT	(3)	→ デジタル方向ボタン右
//#define XINPUT_BUTTON_START		(4)	→ STARTボタン
//#define XINPUT_BUTTON_BACK		(5)	→ BACKボタン
//#define XINPUT_BUTTON_LEFT_THUMB	(6)	→ 左スティック押し込み
//#define XINPUT_BUTTON_RIGHT_THUMB	(7)	→ 右スティック押し込み
//#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	→ LBボタン
//#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	→ RBボタン
//#define XINPUT_BUTTON_A			(12)	→ Aボタン
//#define XINPUT_BUTTON_B			(13)	→ Bボタン
//#define XINPUT_BUTTON_X			(14)	→ Xボタン
//#define XINPUT_BUTTON_Y			(15)	→ Yボタン
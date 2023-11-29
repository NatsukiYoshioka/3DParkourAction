#include"DxLib.h"
#include"common.h"
#include "PadInput.h"

PadInput* PadInput::padInput = nullptr;

PadInput::PadInput():
    input({{initializeNum}})
{

}

//インスタンス生成
void PadInput::CreateInstance()
{
    if (!padInput)
    {
        padInput = new PadInput();
    }
}

//インスタンス破棄
void PadInput::DestroyInstance()
{
    if (padInput)
    {
        delete(padInput);
    }
}

//コントローラー入力情報の更新
void PadInput::Update()
{
    GetJoypadXInputState(DX_INPUT_PAD1, &input);
}
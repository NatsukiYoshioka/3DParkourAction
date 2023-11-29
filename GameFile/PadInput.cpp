#include"DxLib.h"
#include"common.h"
#include "PadInput.h"

PadInput* PadInput::padInput = nullptr;

PadInput::PadInput():
    input({{initializeNum}})
{

}

//�C���X�^���X����
void PadInput::CreateInstance()
{
    if (!padInput)
    {
        padInput = new PadInput();
    }
}

//�C���X�^���X�j��
void PadInput::DestroyInstance()
{
    if (padInput)
    {
        delete(padInput);
    }
}

//�R���g���[���[���͏��̍X�V
void PadInput::Update()
{
    GetJoypadXInputState(DX_INPUT_PAD1, &input);
}
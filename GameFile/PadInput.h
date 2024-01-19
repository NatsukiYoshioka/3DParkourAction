#pragma once
#include<DxLib.h>

/// <summary>
/// �R���g���[���[���͐���N���X
/// </summary>
class PadInput
{
private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PadInput();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PadInput(){}

public:
    /// <summary>
    /// �C���X�^���X����
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �C���X�^���X�j��
    /// </summary>
    static void DestroyInstance();

    /// <summary>
    /// �C���X�^���X�擾
    /// </summary>
    /// <returns>�N���X�̃C���X�^���X</returns>
    static PadInput* GetInstance() { return padInput; }

    /// <summary>
    /// �R���g���[���[���͏��̍X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �R���g���[���[���͏��̎擾
    /// </summary>
    /// <returns>�R���g���[���[���͏��</returns>
    XINPUT_STATE GetInput() { return input; }
private:
    static PadInput* padInput;      //�N���X�C���X�^���X
    XINPUT_STATE input;             //�R���g���[���[���͏��
};

static const int buttonA = 12;

// XInput�{�^�����͒�`
//#define XINPUT_BUTTON_DPAD_UP		(0)	�� �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_DOWN		(1)	�� �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_LEFT		(2)	�� �f�W�^�������{�^����
//#define XINPUT_BUTTON_DPAD_RIGHT	(3)	�� �f�W�^�������{�^���E
//#define XINPUT_BUTTON_START		(4)	�� START�{�^��
//#define XINPUT_BUTTON_BACK		(5)	�� BACK�{�^��
//#define XINPUT_BUTTON_LEFT_THUMB	(6)	�� ���X�e�B�b�N��������
//#define XINPUT_BUTTON_RIGHT_THUMB	(7)	�� �E�X�e�B�b�N��������
//#define XINPUT_BUTTON_LEFT_SHOULDER	(8)	�� LB�{�^��
//#define XINPUT_BUTTON_RIGHT_SHOULDER	(9)	�� RB�{�^��
//#define XINPUT_BUTTON_A			(12)	�� A�{�^��
//#define XINPUT_BUTTON_B			(13)	�� B�{�^��
//#define XINPUT_BUTTON_X			(14)	�� X�{�^��
//#define XINPUT_BUTTON_Y			(15)	�� Y�{�^��
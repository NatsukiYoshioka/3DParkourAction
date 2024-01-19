#pragma once
#include<DxLib.h>
#include"ObjectTag.h"

class GameObject;

/// <summary>
/// UI�I�u�W�F�N�g�Ǘ��N���X
/// </summary>
class UI:public GameObject
{
public:
    /// <summary>
    /// �n���h���ƍ��W�̏�����
    /// </summary>
    /// <param name="textureHandle">�e�N�X�`���n���h��</param>
    /// <param name="pos">�e�N�X�`���̍��W</param>
    UI(int textureHandle, VECTOR pos,int drawTiming);

    /// <summary>
    /// �f�[�^�̉��
    /// </summary>
    ~UI();

    /// <summary>
    /// �I�u�W�F�N�g�̍X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �I�u�W�F�N�g�̕`��
    /// </summary>
    void Draw();

    /// <summary>
    /// �e�N�X�`���n���h���̎擾
    /// </summary>
    /// <returns>�e�N�X�`���n���h��</returns>
    int GetModelHandle() { return modelHandle; }

    /// <summary>
    /// �I�u�W�F�N�g�̃^�O�擾
    /// </summary>
    /// <returns>�I�u�W�F�N�g�^�O</returns>
    ObjectTag GetObjectTag() { return tag; }

    /// <summary>
    /// �I�u�W�F�N�g�̍��W�擾
    /// </summary>
    /// <returns>�I�u�W�F�N�g���W</returns>
    VECTOR GetPos() { return pos; }

private:
    int drawTiming;

    static constexpr int titleIndex = 0;
    static constexpr int inGameIndex = 1;
    static constexpr int resultIndex = 2;

    static constexpr int cursorIndex = 1;

    static constexpr float playCursorX = 350.0f;
    static constexpr float tutorialCursorX = 800.0f;
    static constexpr float exitCursorX = 1250.0f;

    float sizeX;
    float sizeY;

    float dimSize;

    float cursorAngle;

    static constexpr float rotationSpeed = 0.001f;
    static const float maxAngle;

    static constexpr float defaultDimSize = 2.5f;
    static constexpr float cursorDimSize = 2.0f;
    static constexpr float cursorScale = 0.1f;
};


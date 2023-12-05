#pragma once
#include"common.h"
#include<DxLib.h>

class GameObject;

/// <summary>
/// �X�J�C�h�[���̐���N���X
/// </summary>
class Skydome:public GameObject
{
public:
    /// <summary>
    /// �X�J�C�h�[���̏�����
    /// </summary>
    /// <param name="modelHandle">���f���n���h��</param>
    Skydome(int modelHandle);

    /// <summary>
    /// �f�[�^�̊J��
    /// </summary>
    ~Skydome();

    /// <summary>
    /// �X�J�C�h�[���̍X�V
    /// </summary>
    void Update();

    /// <summary>
    /// �X�J�C�h�[���̕`��
    /// </summary>
    void Draw();

    int GetModelHandle() { return initializeNum; }

private:
    static const VECTOR scale;              //�X�J�C�h�[���̑傫��
    static constexpr float height = 350.0f; //�X�J�C�h�[���̍���
};


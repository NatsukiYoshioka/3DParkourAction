#pragma once
#include"ObjectTag.h"
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
    void Update(GameManager::SCENE nowScene);

    /// <summary>
    /// �X�J�C�h�[���̕`��
    /// </summary>
    void Draw();

    /// <summary>
    /// ���f���n���h���擾
    /// </summary>
    /// <returns>���f���n���h��</returns>
    int GetModelHandle() { return initializeNum; }

    /// <summary>
    /// �I�u�W�F�N�g�^�O�擾
    /// </summary>
    /// <returns>�I�u�W�F�N�g�^�O</returns>
    ObjectTag GetObjectTag() { return tag; }

    /// <summary>
    /// ���W�擾
    /// </summary>
    /// <returns>�I�u�W�F�N�g�̍��W</returns>
    VECTOR GetPos() { return pos; }

private:
    static const VECTOR scale;              //�X�J�C�h�[���̑傫��
    static constexpr float height = 350.0f; //�X�J�C�h�[���̍���
};


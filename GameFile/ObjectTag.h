#pragma once

/// <summary>
/// �I�u�W�F�N�g�̃^�O
/// </summary>
enum class ObjectTag :unsigned char
{
    PLAYER,         //�v���C���[�^�O
    CAMERA,         //�J�����^�O
    FIELD,          //�t�B�[���h�^�O
    OBSTACLE,       //��Q���^�O
    SLIDE_OBSTACLE, //��������Q���^�O
    OTHER_OBSTACLE, //���̑��I�u�W�F�N�g
    SKYDOME,        //�X�J�C�h�[���^�O
    UI              //UI�^�O
};
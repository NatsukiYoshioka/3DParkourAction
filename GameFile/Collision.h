#pragma once
#include<DxLib.h>

static constexpr int frameIndex = -1;       //�t���[���̔ԍ�

/// <summary>
/// �t�B�[���h�Ƃ̓����蔻��
/// </summary>
///  <param name="pos">�t�B�[���h�Ɣ�r����I�u�W�F�N�g�̍��W</param>
///  <param name="modelHandle">�t�B�[���h�̃��f���n���h��</param>
///  <param name="linePos1">�����蔻��p������1�_�ڂ̍��W</param>
///  <param name="linePos2">�����蔻��p������2�_�ڂ̍��W</param>
///  <returns>�����������ǂ���</returns>
bool HitFieldJudge(VECTOR &pos,int modelHandle,VECTOR linePos1,VECTOR linePos2);
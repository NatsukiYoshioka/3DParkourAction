#pragma once
#include<DxLib.h>

static constexpr int frameIndex = -1;       //�t���[���̔ԍ�
static constexpr int hitLeft = 1;			//���̕ǂɓ����������̖߂�l
static constexpr int hitRight = 2;			//�E�̕ǂɓ����������̖߂�l

/// <summary>
/// �n�ʂƂ̓����蔻��
/// </summary>
///  <param name="pos">�t�B�[���h�Ɣ�r����I�u�W�F�N�g�̍��W</param>
///  <param name="modelHandle">�t�B�[���h�̃��f���n���h��</param>
///  <param name="linePos1">�����蔻��p������1�_�ڂ̍��W</param>
///  <param name="linePos2">�����蔻��p������2�_�ڂ̍��W</param>
///  <returns>�����������ǂ���</returns>
bool JudgeHitGround(VECTOR &pos,int modelHandle,VECTOR linePos1,VECTOR linePos2);

/// <summary>
/// �ǂƂ̓����蔻��
/// </summary>
///  <param name="pos">�t�B�[���h�Ɣ�r����I�u�W�F�N�g�̍��W</param>
///  <param name="modelHandle">�t�B�[���h�̃��f���n���h��</param>
///  <param name="linePos1">�����蔻��p������1�_�ڂ̍��W</param>
///  <param name="linePos2">�����蔻��p������2�_�ڂ̍��W</param>
///  <returns>�����������ǂ���</returns>
bool JudgeHitWall(VECTOR& pos, int modelHandle, VECTOR linePos1, VECTOR linePos2);

/// <summary>
/// �E�H�[�����������蔻�菈��
/// </summary>
///  <param name="pos">�t�B�[���h�Ɣ�r����I�u�W�F�N�g�̍��W</param>
///  <param name="modelHandle">�t�B�[���h�̃��f���n���h��</param>
///  <param name="linePos1">�����蔻��p������1�_�ڂ̍��W</param>
///  <param name="linePos2">�����蔻��p������2�_�ڂ̍��W</param>
///  <returns>�����������ǂ����A���E�ǂ���̕ǂɓ���������</returns>
int WallRunProcess(VECTOR& pos, int modelHandle, VECTOR linePos1, VECTOR linePos2);
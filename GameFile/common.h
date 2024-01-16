#pragma once
#include"DxLib.h"

const auto SCREEN_WIDTH = 1920;			  //�X�N���[���̉��T�C�Y;
const auto SCREEN_HEIGHT = 1080;          //�X�N���[���̏c�T�C�Y;
const auto SCREEN_COLOR = 16;	          //�X�N���[���J���[;

static const int bipartition = 2;

static const int noHandle = -1;			//�n���h�����K�p����Ă��Ȃ��ꍇ�̒萔
static const int        initializeNum = 0;          //�������萔
static const float      secondFrame = 1000.0f;      //�b�ԃt���[����

static const VECTOR initializePos = VGet(0.0f, 0.0f, 0.0f);		//���W�������萔

static const float pi1_f = 180.0f;		//���W�A���v�Z�p�萔

static const VECTOR transformVector = VGet(0.0f, 0.0f, 0.1f);			//�s�񂩂�x�N�g���ϊ��p�ϐ�
static const VECTOR transformReverseVector = VGet(0.0f, 0.0f, -0.1f);	//�s�񁨃x�N�g���ϊ��t����
static const VECTOR crossVector = VGet(0.0f, 1.0f, 0.0f);		//�O�όv�Z�p�x�N�g��

static constexpr float sceneTransitionTime = 45.0f;			//�V�[���J�ڎ���
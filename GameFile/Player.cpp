#include"GameObject.h"
#include"DxLib.h"
#include "Player.h"

//�I�u�W�F�N�g�̏�����
Player::Player(int modelHandle, vector<int> animationHandle)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	pos = VGet(0.0f, 0.0f, 0.0f);

	this->animationHandle = animationHandle;
	//�v���C���[�̏�����Ԃ����Ⴊ�݂ɂ���
	status = STATUS::CROUCH;
}

//�f�[�^�̉��
Player::~Player()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

//�I�u�W�F�N�g�̍X�V
void Player::Update()
{

}

//�I�u�W�F�N�g�̕`��
void Player::Draw()
{

}
#include"GameObject.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

VECTOR Player::headPos = VGet(0.0f, 0.0f, 0.0f);

//�I�u�W�F�N�g�̏�����
Player::Player(int modelHandle, vector<int> animationHandle):
	input(nullptr)
{
	//�N���X�̃C���X�^���X�擾
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	pos = VGet(960.0f, 540.0f, -200.0f);

	//MV1SetScale(this->modelHandle, VGet(1.0f, 1.0f, 1.0f));
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
	UpdateInput();
	MV1SetPosition(modelHandle, pos);
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
}

void Player::UpdateInput()
{
	//���X�e�B�b�N���|��
	if (input->GetInput().ThumbLX < initializeNum)
	{
		pos.x -= moveSpeed;
	}
	//���X�e�B�b�N�E�|��
	if (input->GetInput().ThumbLX > initializeNum)
	{
		pos.x += moveSpeed;
	}
	//���X�e�B�b�N��|��
	if (input->GetInput().ThumbLY < initializeNum)
	{
		pos.z += moveSpeed;
	}
	//���X�e�B�b�N���|��
	if (input->GetInput().ThumbLY > initializeNum)
	{
		pos.z -= moveSpeed;
	}
}

//�I�u�W�F�N�g�̕`��
void Player::Draw()
{
	MV1DrawModel(modelHandle);
}
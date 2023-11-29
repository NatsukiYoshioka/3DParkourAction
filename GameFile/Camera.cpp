#include"GameObject.h"
#include"Player.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Camera.h"

//�R���X�g���N�^
Camera::Camera():
	rotateV(static_cast<float>(initializeNum))
{
	input = PadInput::GetInstance();
}

//�f�[�^���
Camera::~Camera()
{

}

//�J�����̍X�V
void Camera::Update()
{
	UpdateInput();
	SetCameraPositionAndAngle(Player::GetHeadPos(), Player::GetAngle().x + rotateV, Player::GetAngle().y, Player::GetAngle().z);
}

//���͏����X�V
void Camera::UpdateInput()
{
	//�c�����J�����ړ����͏���
	//�E�X�e�B�b�N��|��
	if (input->GetInput().ThumbRY > initializeNum || CheckHitKey(KEY_INPUT_UP) != initializeNum)
	{
		rotateV -= directionSpeed;
	}
	//�E�X�e�B�b�N���|��
	if (input->GetInput().ThumbRY < initializeNum || CheckHitKey(KEY_INPUT_DOWN) != initializeNum)
	{
		rotateV += directionSpeed;
	}
}
#include"GameObject.h"
#include"ObjectTag.h"
#include"Player.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Camera.h"

//�R���X�g���N�^
Camera::Camera():
	rotateV(static_cast<float>(initializeNum)),
	fov(initializeFov),
	angle(initializePos),
	addPos(initializePos)
{
	tag = ObjectTag::CAMERA;
	input = PadInput::GetInstance();
	SetCameraNearFar(cameraNear, cameraFar);
	//SetupCamera_Perspective(fov);
}

//�f�[�^���
Camera::~Camera()
{

}

//�J�����̍X�V
void Camera::Update()
{
	UpdateInput();

	//�J������Y���W��ݒ�
	pos = Player::GetHeadPos();
	pos.y += fixPosY;

	//�J�����̌������X�V
	angle = Player::GetAngle();
	angle.x += rotateV;

	//�J������O�ɉ����o��
	addPos = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	addPos = VNorm(addPos);
	addPos = VScale(addPos, fixForwardPos);
	pos = VAdd(pos, addPos);

	//�J�����̈ʒu�ƌ������Z�b�g
	SetCameraPositionAndAngle(pos, angle.x, angle.y, angle.z);
}

//���͏����X�V
void Camera::UpdateInput()
{
	//�c�����J�����ړ����͏���
	//�E�X�e�B�b�N��|��
	if (input->GetInput().ThumbRY > initializeNum || CheckHitKey(KEY_INPUT_UP) != initializeNum)
	{
		rotateV -= directionSpeed;
		if (rotateV <= maxUpDirection)
		{
			rotateV = maxUpDirection;
		}
	}
	//�E�X�e�B�b�N���|��
	if (input->GetInput().ThumbRY < initializeNum || CheckHitKey(KEY_INPUT_DOWN) != initializeNum)
	{
		rotateV += directionSpeed;
		if (rotateV >= maxDownDirection)
		{
			rotateV = maxDownDirection;
		}
	}
}
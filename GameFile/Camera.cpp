#include"GameObject.h"
#include"ObjectTag.h"
#include"Player.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Camera.h"

//�R���X�g���N�^
Camera::Camera():
	forwardPos(firstForwardPos),
	rotateV(static_cast<float>(initializeNum)),
	fov(initializeFov),
	angle(initializePos),
	addPos(initializePos)
{
	tag = ObjectTag::CAMERA;
	input = PadInput::GetInstance();
	SetCameraNearFar(cameraNear, cameraFar);
	SetupCamera_Perspective(fov);
}

//�f�[�^���
Camera::~Camera()
{

}

//�I�u�W�F�N�g�̏�����
void Camera::Initialize()
{
	forwardPos=firstForwardPos;
	rotateV=static_cast<float>(initializeNum);
	angle=initializePos;
	addPos=initializePos;
}

//�J�����̍X�V
void Camera::Update()
{
	if(GameManager::GetGameStatus() == GameManager::SCENE::TITLE)Initialize();
	if (GameManager::GetGameStatus() == GameManager::SCENE::GAME)UpdateInput();

	//�J������Y���W��ݒ�
	pos = Player::GetHeadPos();
	pos.y += fixPosY;

	//�J�����̌������X�V
	angle = Player::GetAngle();
	angle.x += rotateV;

	if (GameManager::GetGameStatus() == GameManager::SCENE::GAME)
	{
		forwardPos += (fixForwardPos - firstForwardPos) / sceneTransitionTime;
		if (forwardPos >= fixForwardPos)forwardPos = fixForwardPos;
	}

	//�J������O�ɉ����o��
	addPos = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	addPos = VNorm(addPos);
	addPos = VScale(addPos, forwardPos);
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
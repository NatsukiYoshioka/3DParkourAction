#include"GameObject.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

const VECTOR Player::scale = VGet(0.125f, 0.125f, 0.125f);
const unsigned int Player::capsuleColor = GetColor(255, 255, 0);
VECTOR Player::headPos = initializePos;
VECTOR Player::angle = initializePos;
const VECTOR Player::fixAngle= VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f);

//�I�u�W�F�N�g�̏�����
Player::Player(int modelHandle, vector<int> animationHandle):
	input(nullptr),
	addMove(initializePos),
	status(STATUS::STAND),
	animationIndex(initializeNum),
	totalAnimTime(static_cast<float>(initializeNum)),
	playAnimTime(static_cast<float>(initializeNum)),
	headTopPos(initializePos),
	toePos(initializePos)
{
	//�N���X�̃C���X�^���X�擾
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	MV1SetScale(this->modelHandle, scale);
	pos = VGet(960.0f, 200.0f, -200.0f);

	MV1SetRotationXYZ(this->modelHandle, fixAngle);

	this->animationHandle = animationHandle;

	//�v���C���[�̏�����Ԃ𗧂���Ԃɂ���
	animationIndex = MV1AttachAnim(this->modelHandle, initializeNum, this->animationHandle.at(static_cast<int>(status)));
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
	MV1SetRotationXYZ(modelHandle, VGet(angle.x, angle.y + fixAngle.y, angle.z));
	MV1SetPosition(modelHandle, pos);
	UpdateAnimation();
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	//�����蔻��p�J�v�Z�����W�̌v�Z
	headTopPos = MV1GetFramePosition(modelHandle, headTopFrameIndex);
	toePos = MV1GetFramePosition(modelHandle, toeFrameIndex);
	toePos.x = headTopPos.x;
	toePos.z = headTopPos.z;
	toePos.y += fixToePosY;
}

void Player::UpdateInput()
{
	//���_�ړ����͏���
	//�E�X�e�B�b�N���|��
	if (input->GetInput().ThumbRX < initializeNum || CheckHitKey(KEY_INPUT_LEFT) != initializeNum)
	{
		angle.y -= directionSpeed;
	}
	//�E�X�e�B�b�N�E�|��
	if (input->GetInput().ThumbRX > initializeNum || CheckHitKey(KEY_INPUT_RIGHT) != initializeNum)
	{
		angle.y += directionSpeed;
	}

	status = STATUS::STAND;

	//�ړ����͏���
	//���X�e�B�b�N���|��
	if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
	{
		addMove= VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VCross(addMove, VGet(0.0f, 1.0f, 0.0f));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

		status = STATUS::RUN_LEFT;
	}
	//���X�e�B�b�N�E�|��
	if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VCross(addMove, VGet(0.0f, 1.0f, 0.0f));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

		status = STATUS::RUN_RIGHT;
	}
	//���X�e�B�b�N��|��
	if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

		status = STATUS::RUN;
	}
	//���X�e�B�b�N���|��
	if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

		status = STATUS::RUN_BACK;
	}
}

//�A�j���[�V�����̍X�V
void Player::UpdateAnimation()
{
	//�A�j���[�V�����̃A�^�b�`
	MV1DetachAnim(modelHandle, animationIndex);
	animationIndex = MV1AttachAnim(modelHandle, initializeNum, animationHandle.at(static_cast<int>(status)));
	//�A�j���[�V�����̍Đ�
	totalAnimTime = MV1GetAttachAnimTotalTime(modelHandle, animationIndex);
	playAnimTime += animationSpeed;
	if (playAnimTime >= totalAnimTime)
	{
		playAnimTime = static_cast<float>(initializeNum);
	}
	MV1SetAttachAnimTime(modelHandle, animationIndex, playAnimTime);
}

//�����蔻��
void Player::OnCollisionEnter(const GameObject* other)
{

}

//�I�u�W�F�N�g�̕`��
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	//�����蔻��f�o�b�O�p�J�v�Z���`��
	DrawCapsule3D(headTopPos, toePos, capsuleWidth, capsuleDivNum, capsuleColor, capsuleColor, FALSE);
}
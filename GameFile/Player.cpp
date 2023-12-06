#include"GameObject.h"
#include"ObjectTag.h"
#include"PadInput.h"
#include"Collision.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

const VECTOR Player::scale = VGet(0.125f, 0.125f, 0.125f);
const unsigned int Player::debugColor = GetColor(255, 255, 0);
VECTOR Player::headPos = initializePos;
VECTOR Player::angle = initializePos;
const VECTOR Player::fixAngle= VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f);

//�I�u�W�F�N�g�̏�����
Player::Player(int modelHandle, vector<int> animationHandle):
	input(nullptr),
	addMove(initializePos),
	isGround(false),
	gravity(static_cast<float>(initializeNum)),
	status(STATUS::STAND),
	animationIndex(initializeNum),
	totalAnimTime(static_cast<float>(initializeNum)),
	playAnimTime(static_cast<float>(initializeNum)),
	groundLinePos()
{
	tag = ObjectTag::PLAYER;
	//�N���X�̃C���X�^���X�擾
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	MV1SetScale(this->modelHandle, scale);
	pos = VGet(1000.0f, 400.0f, 0.0f);

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
	//UpdateGravity();
	MV1SetPosition(modelHandle, pos);
	UpdateAnimation();
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	//�����蔻��p�����̍��W�v�Z
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		for (int j = initializeNum; j < lineNum; j++)
		{
			//������1�_�ڂ̍��W�ݒ�
			if (j == initializeNum)
			{
				addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			}
			//������2�_�ڂ̍��W�ݒ�
			else
			{
				addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				
			}
			addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, lineSpace);
			groundLinePos[i][j] = VAdd(pos, addMove);
			addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

			addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, (i - lineNum) * (lineSpace * lineNum / lineDivNum));
			groundLinePos[i][j] = VAdd(groundLinePos[i][j], addMove);
			addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));
		}
	}
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

//�d�͏����̍X�V
void Player::UpdateGravity()
{
	gravity += addGravity;
	if (gravity >= maxGravity)
	{
		gravity = maxGravity;
	}
	pos.y -= gravity;
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
void Player::OnCollisionEnter(GameObject* other,const ObjectTag tag)
{
	if (tag == ObjectTag::FIELD)
	{
		for (int i = initializeNum; i < lineDivNum; i++)
		{
			HitFieldJudge(pos, other->GetModelHandle(), groundLinePos[i][0], groundLinePos[i][1]);
		}
	}
	if (tag == ObjectTag::OBSTACLE)
	{

	}
}

//�I�u�W�F�N�g�̕`��
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	//�����蔻��f�o�b�O�p�`��
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		DrawLine3D(groundLinePos[i][0], groundLinePos[i][1], debugColor);
	}
}
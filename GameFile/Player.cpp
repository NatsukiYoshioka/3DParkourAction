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
	moveDirection(initializePos),
	moveDirectionX(initializePos),
	moveDirectionZ(initializePos),
	isHitWall(initializeNum),
	isLeft(false),
	isGround(false),
	isJump(false),
	isMove(false),
	isWallRun(false),
	gravity(static_cast<float>(initializeNum)),
	jump(static_cast<float>(initializeNum)),
	status(STATUS::STAND),
	animationIndex(initializeNum),
	totalAnimTime(static_cast<float>(initializeNum)),
	playAnimTime(static_cast<float>(initializeNum)),
	groundLinePos(),
	wallCollisionLinePos()
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
	UpdateGravity();
	MV1SetPosition(modelHandle, pos);
	UpdateAnimation();
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	//�����蔻��p�����̍��W�v�Z
	CalcCollisionLine();
}

void Player::UpdateInput()
{
	//���_�ړ����͏���
	if (!isWallRun)
	{
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
	}

	//�ړ����͏���
	if (isGround && !isWallRun)
	{
		isMove = false;
		status = STATUS::STAND;
		//���X�e�B�b�N���|��
		if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
		{
			pos = VAdd(pos, CalcLeftMove(addMove));

			isMove = true;
			status = STATUS::RUN_LEFT;
		}
		//���X�e�B�b�N�E�|��
		if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
		{
			pos = VAdd(pos, CalcRightMove(addMove));

			isMove = true;
			status = STATUS::RUN_RIGHT;
		}
		//���X�e�B�b�N��|��
		if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
		{
			pos = VAdd(pos, CalcFrontMove(addMove));

			isMove = true;
			status = STATUS::RUN;
		}
		//���X�e�B�b�N���|��
		if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
		{
			pos = VAdd(pos, CalcBehindMove(addMove));

			isMove = true;
			status = STATUS::RUN_BACK;
		}

		//�A�N�V�������͏���
		//�W�����v:A�{�^������
		if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
		{
			isJump = true;
			moveDirectionX = initializePos;
			moveDirectionZ = initializePos;
			//���X�e�B�b�N���|��
			if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
			}
			//���X�e�B�b�N�E�|��
			if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
			}
			//���X�e�B�b�N��|��
			if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
			{
				moveDirectionZ = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionZ = VNorm(moveDirectionZ);
			}
			//���X�e�B�b�N���|��
			if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
			{
				moveDirectionZ = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionZ = VNorm(moveDirectionZ);
			}
			moveDirection = VAdd(moveDirectionX, moveDirectionZ);
			moveDirection = VNorm(moveDirection);
			jump = jumpPower;
			gravity = static_cast<float>(initializeNum);

			isGround = false;
			status = STATUS::JUMP;
			playAnimTime = static_cast<float>(initializeNum);
		}
	}
	else if (isWallRun)
	{
		isMove = false;
		//���X�e�B�b�N��|��
		if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
		{
			pos = VAdd(pos, CalcFrontMove(addMove));
		}
		if (isLeft)
		{
			//���X�e�B�b�N���|��
			if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
			{
				pos = VAdd(pos, CalcLeftMove(addMove));
			}
		}
		else
		{
			//���X�e�B�b�N�E�|��
			if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
			{
				pos = VAdd(pos, CalcRightMove(addMove));
			}
		}
		//�W�����v:A�{�^������
		if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
		{
			moveDirectionZ = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			moveDirectionZ = VNorm(moveDirectionZ);
			isMove = true;
			if (isLeft)
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
				pos = VAdd(pos, CalcRightMove(addMove));
			}
			else
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
				pos = VAdd(pos, CalcLeftMove(addMove));
			}
			moveDirection = VAdd(moveDirectionX, moveDirectionZ);
			moveDirection = VNorm(moveDirection);
			jump = jumpPower;
			gravity = static_cast<float>(initializeNum);

			status = STATUS::JUMP;
			playAnimTime = static_cast<float>(initializeNum);
			isWallRun = false;
		}
	}
	else
	{
		//�󒆂ł̃v���C���[�̋���
		if (isMove)
		{
			pos = VAdd(pos, VScale(moveDirection, moveSpeed));
		}
		jump -= addGravity;
		if (jump <= static_cast<float>(initializeNum))
		{
			jump = static_cast<float>(initializeNum);
		}
		if (status != STATUS::JUMP)
		{
			status = STATUS::FALL;
		}
		pos.y += jump;
	}
}

VECTOR Player::CalcLeftMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VCross(vec, VGet(0.0f, 1.0f, 0.0f));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

VECTOR Player::CalcRightMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VCross(vec, VGet(0.0f, 1.0f, 0.0f));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

VECTOR Player::CalcFrontMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

VECTOR Player::CalcBehindMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

//�d�͏����̍X�V
void Player::UpdateGravity()
{
	if (jump <= static_cast<float>(initializeNum))
	{
		gravity += addGravity;
		isGround = false;
	}
	
	if (gravity >= maxGravity)
	{
		gravity = maxGravity;
	}
	if (isWallRun)gravity = static_cast<float>(initializeNum);
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
		switch (status)
		{
		case STATUS::JUMP:
			status = STATUS::FALL;
			break;
		default:
			playAnimTime = static_cast<float>(initializeNum);
			break;
		}
	}

	MV1SetAttachAnimTime(modelHandle, animationIndex, playAnimTime);
}

//�����蔻������̌v�Z
void Player::CalcCollisionLine()
{
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		for (int j = initializeNum; j < lineDivNum; j++)
		{
			//�n�ʂ̓����蔻�����
			addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, static_cast<float>((i - lineNum) * (groundLineSpace * lineDivNum / lineNum)));
			groundLinePos[i][j] = VAdd(VGet(pos.x, pos.y + groundLineWidth - maxGravity, pos.z), addMove);

			addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, static_cast<float>((j - lineNum) * (groundLineSpace * lineDivNum / lineNum)));
			groundLinePos[i][j] = VAdd(groundLinePos[i][j], addMove);

			//�ǂ̓����蔻��p����
			for (int l = initializeNum; l < lineNum; l++)
			{
				if(l == initializeNum)
				{
					addMove = VTransform(VGet(0.1f, 0.0f, 0.0f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				}
				else addMove = VTransform(VGet(-0.1f, 0.0f, 0.0f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, wallCollisionLineWidth);
				wallCollisionLinePos[l][i][j] = VAdd(VGet(pos.x, pos.y + fixWallCollisionLinePosY, pos.z), addMove);

				addMove = VTransform(VGet(0.1f, 0.0f, 0.0f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, static_cast<float>((i - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum)));
				wallCollisionLinePos[l][i][j] = VAdd(wallCollisionLinePos[l][i][j], addMove);

				wallCollisionLinePos[l][i][j].y += static_cast<float>((j - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum));
			}

			//���ʂ̓����蔻��p����
			for (int l = initializeNum; l < lineNum; l++)
			{
				if (l == initializeNum)
				{
					addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				}
				else addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, wallCollisionLineWidth);
				sideCollisionLinePos[l][i][j] = VAdd(VGet(pos.x, pos.y + fixWallCollisionLinePosY, pos.z), addMove);

				addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, static_cast<float>((i - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum)));
				sideCollisionLinePos[l][i][j] = VAdd(sideCollisionLinePos[l][i][j], addMove);

				sideCollisionLinePos[l][i][j].y += static_cast<float>((j - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum));
			}
		}
	}
}

//�����蔻��
void Player::OnCollisionEnter(GameObject* other,const ObjectTag tag)
{
	if (tag == ObjectTag::FIELD)
	{
		for (int i = initializeNum; i < lineDivNum; i++)
		{
			for (int j = initializeNum; j < lineDivNum; j++)
			{
				if (HitGroundJudge(pos, other->GetModelHandle(), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y + groundLineWidth, groundLinePos[i][j].z), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y - groundLineWidth, groundLinePos[i][j].z)))
				{
					CalcCollisionLine();
					isGround = true;
					isJump = false;
				}
				if (isGround)
				{
					if (HitWallJudge(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]))
					{
						CalcCollisionLine();
					}
				}
				else
				{
					isHitWall = WallRunProcess(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]);
					if (isHitWall && isJump)
					{
						if (isHitWall == hitLeft)isLeft = true;
						else isLeft = false;
						isWallRun = true;
						CalcCollisionLine();
					}
				}
				if (HitWallJudge(pos, other->GetModelHandle(), wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j]))
				{
					CalcCollisionLine();
				}
			}
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
		for (int j = initializeNum; j < lineDivNum; j++)
		{
			DrawLine3D(VGet(groundLinePos[i][j].x, groundLinePos[i][j].y + groundLineWidth, groundLinePos[i][j].z), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y - groundLineWidth, groundLinePos[i][j].z), debugColor);
			DrawLine3D(wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j], debugColor);
			DrawLine3D(sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j], debugColor);
		}
	}
}
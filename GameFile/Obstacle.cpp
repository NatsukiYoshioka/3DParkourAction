#include"DxLib.h"
#include"GameObject.h"
#include"Player.h"
#include"ObjectTag.h"
#include"common.h"
#include "Obstacle.h"

const VECTOR Obstacle::scale = VGet(0.04f, 0.04f, 0.04f);

//���f���̎擾�ƍ��W�̏�����
Obstacle::Obstacle(int modelHandle, VECTOR pos, float angle, int isSlide):
	angle(initializePos)
{
	if (isSlide)tag = ObjectTag::SLIDE_OBSTACLE;
	else tag = ObjectTag::OBSTACLE;
	
	this->modelHandle = MV1DuplicateModel(modelHandle);
	this->pos = pos;
	this->angle.y = angle;

	MV1SetRotationXYZ(this->modelHandle, this->angle);
	MV1SetScale(this->modelHandle, scale);

	MV1SetPosition(this->modelHandle, this->pos);
	MV1SetupCollInfo(this->modelHandle, frameIndex, collisionDivNum, collisionDivNum, collisionDivNum);
}

//�f�[�^�̉��
Obstacle::~Obstacle()
{
	if (modelHandle != noHandle)
	{
		MV1DeleteModel(modelHandle);
	}
}

//�I�u�W�F�N�g�̍X�V
void Obstacle::Update()
{
	MV1SetPosition(modelHandle, pos);
}

//�I�u�W�F�N�g�̕`��
void Obstacle::Draw()
{
	if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
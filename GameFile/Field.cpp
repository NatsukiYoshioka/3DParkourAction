#include"DxLib.h"
#include"ObjectTag.h"
#include"common.h"
#include"GameObject.h"
#include "Field.h"

//���f���̎擾�ƍ��W�Ɗp�x�̏�����
Field::Field(int modelHandle, VECTOR pos,float angle):
	angle(initializePos)
{
	tag = ObjectTag::FIELD;
	this->modelHandle = MV1DuplicateModel(modelHandle);
	this->pos = pos;
	this->angle.y = angle;

	MV1SetRotationXYZ(this->modelHandle, this->angle);

	MV1SetupCollInfo(frameIndex, collisionDivNum, collisionDivNum, collisionDivNum);
}

//�f�[�^�̉��
Field::~Field()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

//�I�u�W�F�N�g�̍X�V
void Field::Update()
{
	MV1SetPosition(modelHandle, pos);
}

//�I�u�W�F�N�g�̕`��
void Field::Draw()
{
	if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
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

	MV1SetPosition(this->modelHandle, this->pos);
	MV1SetupCollInfo(this->modelHandle, frameIndex, collisionDivNum, collisionDivNum, collisionDivNum);
}

//�f�[�^�̉��
Field::~Field()
{
	if (modelHandle != noHandle)
	{
		MV1DeleteModel(modelHandle);
	}
}

//�I�u�W�F�N�g�̍X�V
void Field::Update()
{
	
}

//�I�u�W�F�N�g�̕`��
void Field::Draw()
{
	if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
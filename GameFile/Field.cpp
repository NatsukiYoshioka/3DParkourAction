#include"DxLib.h"
#include"common.h"
#include"GameObject.h"
#include "Field.h"

//���f���̎擾�ƍ��W�̏�����
Field::Field(int modelHandle, VECTOR pos)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	MV1SetScale(this->modelHandle, VGet(1.0f, 1.0f, 1.0f));
	this->pos = pos;
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
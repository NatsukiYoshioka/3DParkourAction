#include"DxLib.h"
#include"GameObject.h"
#include"common.h"
#include "Obstacle.h"

//���f���̎擾�ƍ��W�̏�����
Obstacle::Obstacle(int modelHandle, VECTOR pos)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	this->pos = pos;
}

//�f�[�^�̉��
Obstacle::~Obstacle()
{
	if (modelHandle != -1)
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
	if (pos.x != static_cast<float>(initializeNum) && pos.y != static_cast<float>(initializeNum) && pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
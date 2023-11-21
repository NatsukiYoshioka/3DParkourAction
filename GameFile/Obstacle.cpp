#include"DxLib.h"
#include"GameObject.h"
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

}

//�I�u�W�F�N�g�̕`��
void Obstacle::Draw()
{

}
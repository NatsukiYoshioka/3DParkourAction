#include"DxLib.h"
#include"GameObject.h"
#include "Field.h"

//���f���̎擾�ƍ��W�̏�����
Field::Field(int modelHandle, VECTOR pos)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
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

}

//�I�u�W�F�N�g�̕`��
void Field::Draw()
{

}
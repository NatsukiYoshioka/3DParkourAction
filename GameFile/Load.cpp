#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include"DxLib.h"
#include"common.h"
#include "Load.h"

Load* Load::load = nullptr;

//�R���X�g���N�^
Load::Load():
	isHeader(false),
	isIndex(false),
	playerModelHandle(-1)
{

}

//�f�[�^�̉��
Load::~Load()
{
	if (playerModelHandle != -1)
	{
		MV1DeleteModel(playerModelHandle);
	}
	for (int i = initializeNum; i < fieldModelHandle.size(); i++)
	{
		if (fieldModelHandle.at(i) != -1)
		{
			MV1DeleteModel(fieldModelHandle.at(i));
		}
	}
	for (int i = initializeNum; i < obstacleModelHandle.size(); i++)
	{
		if (obstacleModelHandle.at(i) != -1)
		{
			MV1DeleteModel(obstacleModelHandle.at(i));
		}
	}
}

//�C���X�^���X����
void Load::CreateInstance()
{
	if (!load)
	{
		load = new Load();
	}
}

//�C���X�^���X�j��
void Load::DestroyInstance()
{
	if (load)
	{
		delete(load);
	}
}

//�t�@�C������f�[�^�擾
void Load::ReadFile(string filePath, bool isHeader, bool isIndex)
{
	this->filePath = filePath;
	this->isHeader = isHeader;
	this->isIndex = isIndex;

	string buf;
	string commaBuf;

	//�ǂݍ���csv�t�@�C�����J��
	ifstream file(this->filePath);

	//getline�֐���1�s���ǂݍ����buf�Ɋi�[
	for (int i = initializeNum; getline(file, buf); i++)
	{
		cell.push_back(vector<string>());

		//delim��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�ɂ���
		istringstream iStream(buf);

		for (int j = initializeNum; getline(iStream, commaBuf, delim); j++)
		{
			if (this->isHeader && this->isIndex)
			{
				if (i == initializeNum && j == initializeNum)continue;
				//�w�b�_�[���̊i�[
				if (i == initializeNum && j != initializeNum)header.push_back(commaBuf);
				//�C���f�b�N�X���̊i�[
				if (i != initializeNum && j == initializeNum)index.push_back(commaBuf);
				//�v�f�̊i�[
				if (i != initializeNum && j != initializeNum)cell.at(i).push_back(commaBuf);
			}
			else if (this->isHeader)
			{
				//�w�b�_�[���̊i�[
				if (i == initializeNum)header.push_back(commaBuf);
				//�C���f�b�N�X���̊i�[
				if (i != initializeNum && j == initializeNum)index.push_back(string());
				//�v�f�̊i�[
				if (i != initializeNum)cell.at(i).push_back(commaBuf);
			}
			else if (this->isIndex)
			{
				//�w�b�_�[���̊i�[
				if (i == initializeNum && j != initializeNum)header.push_back(string());
				//�C���f�b�N�X���̊i�[
				if (j == initializeNum)index.push_back(commaBuf);
				//�v�f�̊i�[
				if (j != initializeNum)cell.at(i).push_back(commaBuf);
			}
			else
			{
				//�w�b�_�[���̊i�[
				if (i == initializeNum)header.push_back(string());
				//�C���f�b�N�X���̊i�[
				if (j == initializeNum)index.push_back(string());
				//�v�f�̊i�[
				cell.at(i).push_back(commaBuf);
			}
		}
	}
}

//�f�[�^�̃��[�h
void Load::LoadData()
{
	for (int i = initializeNum; i < cell.size(); i++)
	{
		for (int j = initializeNum; j < cell.at(i).size(); j++)
		{
			//�v���C���[���f���̃��[�h
			if (header.at(j) == playerHeader && cell.at(i).at(j) != "")
			{
				playerModelHandle = MV1LoadModel(cell.at(i).at(j).c_str());
			}
			//�v���C���[�̃A�j���[�V���������[�h
			if (header.at(j) == animationHeader && cell.at(i).at(j) != "")
			{
				playerAnimationHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
			//�t�B�[���h���f���̃��[�h
			if (header.at(j) == fieldHeader && cell.at(i).at(j) != "")
			{
				fieldModelHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
			//��Q�����f���̃��[�h
			if (header.at(j) == obstacleHeader && cell.at(i).at(j) != "")
			{
				obstacleModelHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
			//�t�B�[���h�̍��W�擾
			if (header.at(j) == fieldPosXHeader && cell.at(i).at(j) != "")
			{
				fieldPos.push_back({ stof(cell.at(i).at(j)),stof(cell.at(i).at(j + 1)),stof(cell.at(i).at(j + 2)) });
			}
			//�t�B�[���h�̊p�x���擾
			if (header.at(j) == fieldAngleHeader && cell.at(i).at(j) != "")
			{
				fieldAngle.push_back(stof(cell.at(i).at(j)) * DX_PI_F / pi1_f);
			}
			//��Q���̍��W�擾
			if (header.at(j) == obstaclePosXHeader && cell.at(i).at(j) != "")
			{
				obstaclePos.push_back({ stof(cell.at(i).at(j)) ,stof(cell.at(i).at(j + 1)) ,stof(cell.at(i).at(j + 2)) });
			}
			//�X�J�C�h�[���̃��f���̃��[�h
			if (header.at(j) == skydomeHeader && cell.at(i).at(j) != "")
			{
				skydomeModelHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
		}
	}
}
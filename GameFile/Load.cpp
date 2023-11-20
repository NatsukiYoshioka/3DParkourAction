#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include"common.h"
#include "Load.h"

Load::Load():
	isHeader(false),
	isIndex(false)
{

}

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
				if (i != initializeNum && j != initializeNum)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else if (this->isHeader)
			{
				//�w�b�_�[���̊i�[
				if (i == 0)header.push_back(commaBuf);
				//�C���f�b�N�X���̊i�[
				if (i != 0 && j == 0)index.push_back(string());
				//�v�f�̊i�[
				if (i != 0)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else if (this->isIndex)
			{
				//�w�b�_�[���̊i�[
				if (i == 0 && j != 0)header.push_back(string());
				//�C���f�b�N�X���̊i�[
				if (j == 0)index.push_back(commaBuf);
				//�v�f�̊i�[
				if (j != 0)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else
			{
				//�w�b�_�[���̊i�[
				if (i == 0)header.push_back(string());
				//�C���f�b�N�X���̊i�[
				if (j == 0)index.push_back(string());
				//�v�f�̊i�[
				cell.at(i).push_back(CastCell(commaBuf));
			}
		}
	}
}

void Load::LoadModel()
{
	for (int i = 0; i < index.size(); i++)
	{
		for (int j=0; header.size(); j++)
		{
			if (header.at(j) == "PLAYER")
			{

			}
		}
	}
}
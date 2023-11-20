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

	//読み込むcsvファイルを開く
	ifstream file(this->filePath);

	//getline関数で1行ずつ読み込んでbufに格納
	for (int i = initializeNum; getline(file, buf); i++)
	{
		cell.push_back(vector<string>());

		//delim区切りごとにデータを読み込むためにistringstreamにする
		istringstream iStream(buf);

		for (int j = initializeNum; getline(iStream, commaBuf, delim); j++)
		{
			if (this->isHeader && this->isIndex)
			{
				if (i == initializeNum && j == initializeNum)continue;
				//ヘッダー情報の格納
				if (i == initializeNum && j != initializeNum)header.push_back(commaBuf);
				//インデックス情報の格納
				if (i != initializeNum && j == initializeNum)index.push_back(commaBuf);
				//要素の格納
				if (i != initializeNum && j != initializeNum)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else if (this->isHeader)
			{
				//ヘッダー情報の格納
				if (i == 0)header.push_back(commaBuf);
				//インデックス情報の格納
				if (i != 0 && j == 0)index.push_back(string());
				//要素の格納
				if (i != 0)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else if (this->isIndex)
			{
				//ヘッダー情報の格納
				if (i == 0 && j != 0)header.push_back(string());
				//インデックス情報の格納
				if (j == 0)index.push_back(commaBuf);
				//要素の格納
				if (j != 0)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else
			{
				//ヘッダー情報の格納
				if (i == 0)header.push_back(string());
				//インデックス情報の格納
				if (j == 0)index.push_back(string());
				//要素の格納
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
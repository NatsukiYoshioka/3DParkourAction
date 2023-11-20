#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include"DxLib.h"
#include"common.h"
#include "Load.h"

Load* Load::load = nullptr;

//コンストラクタ
Load::Load():
	isHeader(false),
	isIndex(false),
	playerModelHandle(-1)
{

}

//データの解放
Load::~Load()
{
	if (playerModelHandle != -1)
	{
		MV1DeleteModel(playerModelHandle);
	}
	for (int i = 0; fieldModelHandle.size(); i++)
	{
		if (fieldModelHandle.at(i) != -1)
		{
			MV1DeleteModel(fieldModelHandle.at(i));
		}
	}
	for (int i = 0; obstacleModelHandle.size(); i++)
	{
		if (obstacleModelHandle.at(i) != -1)
		{
			MV1DeleteModel(obstacleModelHandle.at(i));
		}
	}
}

//インスタンス生成
void Load::CreateInstance()
{
	if (!load)
	{
		load = new Load();
	}
}

//インスタンス破棄
void Load::DestroyInstance()
{
	if (load)
	{
		delete(load);
	}
}

//ファイルからデータ取得
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
				if (i != initializeNum && j != initializeNum)cell.at(i - 1).push_back(commaBuf);
			}
			else if (this->isHeader)
			{
				//ヘッダー情報の格納
				if (i == 0)header.push_back(commaBuf);
				//インデックス情報の格納
				if (i != 0 && j == 0)index.push_back(string());
				//要素の格納
				if (i != 0)cell.at(i - 1).push_back(commaBuf);
			}
			else if (this->isIndex)
			{
				//ヘッダー情報の格納
				if (i == 0 && j != 0)header.push_back(string());
				//インデックス情報の格納
				if (j == 0)index.push_back(commaBuf);
				//要素の格納
				if (j != 0)cell.at(i - 1).push_back(commaBuf);
			}
			else
			{
				//ヘッダー情報の格納
				if (i == 0)header.push_back(string());
				//インデックス情報の格納
				if (j == 0)index.push_back(string());
				//要素の格納
				cell.at(i).push_back(commaBuf);
			}
		}
	}
}

//データのロード
void Load::LoadData()
{
	for (int i = 0; i < index.size(); i++)
	{
		for (int j=0; header.size(); j++)
		{
			//プレイヤーモデルのロード
			if (header.at(j) == "PLAYER" && cell.at(i).at(j) != "")
			{
				playerModelHandle = MV1LoadModel(cell.at(i).at(j).c_str());
			}
			//フィールドモデルのロード
			if (header.at(j) == "FIELD" && cell.at(i).at(j) != "")
			{
				fieldModelHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
			//障害物モデルのロード
			if (header.at(j) == "OBSTACLE" && cell.at(i).at(j) != "")
			{
				obstacleModelHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
		}
	}
}
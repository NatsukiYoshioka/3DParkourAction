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
	playerModelHandle(noHandle),
	tempFieldModelHandle(noHandle),
	tempObstacleModelHandle(noHandle),
	tempUITextureHandle(noHandle)
{

}

//データの解放
Load::~Load()
{
	if (playerModelHandle != noHandle)
	{
		MV1DeleteModel(playerModelHandle);
	}
	for (int i = initializeNum; i < fieldModelHandle.size(); i++)
	{
		if (fieldModelHandle.at(i) != noHandle)
		{
			MV1DeleteModel(fieldModelHandle.at(i));
		}
	}
	for (int i = initializeNum; i < obstacleModelHandle.size(); i++)
	{
		if (obstacleModelHandle.at(i) != noHandle)
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
				if (i != initializeNum && j != initializeNum)cell.at(i).push_back(commaBuf);
			}
			else if (this->isHeader)
			{
				//ヘッダー情報の格納
				if (i == initializeNum)header.push_back(commaBuf);
				//インデックス情報の格納
				if (i != initializeNum && j == initializeNum)index.push_back(string());
				//要素の格納
				if (i != initializeNum)cell.at(i).push_back(commaBuf);
			}
			else if (this->isIndex)
			{
				//ヘッダー情報の格納
				if (i == initializeNum && j != initializeNum)header.push_back(string());
				//インデックス情報の格納
				if (j == initializeNum)index.push_back(commaBuf);
				//要素の格納
				if (j != initializeNum)cell.at(i).push_back(commaBuf);
			}
			else
			{
				//ヘッダー情報の格納
				if (i == initializeNum)header.push_back(string());
				//インデックス情報の格納
				if (j == initializeNum)index.push_back(string());
				//要素の格納
				cell.at(i).push_back(commaBuf);
			}
		}
	}
}

//データのロード
void Load::LoadData()
{
	for (int i = initializeNum; i < cell.size(); i++)
	{
		for (int j = initializeNum; j < cell.at(i).size(); j++)
		{
			//プレイヤーモデルのロード
			if (header.at(j) == playerHeader && cell.at(i).at(j) != "")
			{
				playerModelHandle = MV1LoadModel(cell.at(i).at(j).c_str());
			}
			//プレイヤーのアニメーションをロード
			if (header.at(j) == animationHeader && cell.at(i).at(j) != "")
			{
				playerAnimationHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
			//フィールドモデルのロード
			if (header.at(j) == fieldHeader && cell.at(i).at(j) == "same")
			{
				fieldModelHandle.push_back(MV1DuplicateModel(tempFieldModelHandle));
			}
			else if (header.at(j) == fieldHeader && cell.at(i).at(j) != "")
			{
				tempFieldModelHandle = MV1LoadModel(cell.at(i).at(j).c_str());
				fieldModelHandle.push_back(MV1DuplicateModel(tempFieldModelHandle));
			}
			//障害物モデルのロード
			if (header.at(j) == obstacleHeader && cell.at(i).at(j) == "same")
			{
				obstacleModelHandle.push_back(MV1DuplicateModel(tempObstacleModelHandle));
			}
			else if (header.at(j) == obstacleHeader && cell.at(i).at(j) != "")
			{
				tempObstacleModelHandle = MV1LoadModel(cell.at(i).at(j).c_str());
				obstacleModelHandle.push_back(MV1DuplicateModel(tempObstacleModelHandle));
			}
			//フィールドの座標取得
			if (header.at(j) == fieldPosXHeader && cell.at(i).at(j) != "")
			{
				fieldPos.push_back({ stof(cell.at(i).at(j)),stof(cell.at(i).at(j + 1)),stof(cell.at(i).at(j + 2)) });
			}
			//フィールドの角度を取得
			if (header.at(j) == fieldAngleHeader && cell.at(i).at(j) != "")
			{
				fieldAngle.push_back(stof(cell.at(i).at(j)) * DX_PI_F / pi1_f);
			}
			//障害物の座標取得
			if (header.at(j) == obstaclePosXHeader && cell.at(i).at(j) != "")
			{
				obstaclePos.push_back({ stof(cell.at(i).at(j)) ,stof(cell.at(i).at(j + 1)) ,stof(cell.at(i).at(j + 2)) });
			}
			//障害物の角度取得
			if (header.at(j) == obstacleAngleHeader && cell.at(i).at(j) != "")
			{
				obstacleAngle.push_back(stof(cell.at(i).at(j)) * DX_PI_F / pi1_f);
			}
			//障害物がくぐれるか取得
			if (header.at(j) == obstacleObstacleTypeHeader && cell.at(i).at(j) != "")
			{
				obstacleType.push_back(stoi(cell.at(i).at(j)));
			}
			//スカイドームのモデルのロード
			if (header.at(j) == skydomeHeader && cell.at(i).at(j) != "")
			{
				skydomeModelHandle.push_back(MV1LoadModel(cell.at(i).at(j).c_str()));
			}
			//スカイドームの座標取得
			if (header.at(j) == skydomePosXHeader && cell.at(i).at(j) != "")
			{
				skydomePos.push_back({ stof(cell.at(i).at(j)) ,stof(cell.at(i).at(j + 1)) ,stof(cell.at(i).at(j + 2)) });
			}
			//UIテクスチャのロード
			if (header.at(j) == UIHeader && cell.at(i).at(j) == "same")
			{
				UITextureHandle.push_back(tempUITextureHandle);
			}
			else if (header.at(j) == UIHeader && cell.at(i).at(j) != "")
			{
				tempUITextureHandle = LoadGraph(cell.at(i).at(j).c_str());
				UITextureHandle.push_back(tempUITextureHandle);
			}
			//UI座標の取得
			if (header.at(j) == UIPosXHeader && cell.at(i).at(j) != "")
			{
				UIPos.push_back({ stof(cell.at(i).at(j)) ,stof(cell.at(i).at(j + 1)) ,stof(cell.at(i).at(j + 2)) });
			}
			//UIを描画するタイミングを取得
			if (header.at(j) == UIDrawTimingHeader && cell.at(i).at(j) != "")
			{
				UIDrawTiming.push_back(stoi(cell.at(i).at(j)));
			}
			//フォントパスの取得
			if (header.at(j) == fontHeader && cell.at(i).at(j) != "")
			{
				fontPath.push_back(cell.at(i).at(j).c_str());
			}
		}
	}
}
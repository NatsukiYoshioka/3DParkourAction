#include"DxLib.h"
#include"GameObject.h"
#include"common.h"
#include "Obstacle.h"

//モデルの取得と座標の初期化
Obstacle::Obstacle(int modelHandle, VECTOR pos)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	this->pos = pos;
}

//データの解放
Obstacle::~Obstacle()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

//オブジェクトの更新
void Obstacle::Update()
{
	MV1SetPosition(modelHandle, pos);
}

//オブジェクトの描画
void Obstacle::Draw()
{
	if (pos.x != static_cast<float>(initializeNum) && pos.y != static_cast<float>(initializeNum) && pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
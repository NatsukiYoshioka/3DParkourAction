#include"DxLib.h"
#include"GameObject.h"
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

}

//オブジェクトの描画
void Obstacle::Draw()
{

}
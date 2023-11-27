#include"DxLib.h"
#include"common.h"
#include"GameObject.h"
#include "Field.h"

//モデルの取得と座標の初期化
Field::Field(int modelHandle, VECTOR pos)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	MV1SetScale(this->modelHandle, VGet(1.0f, 1.0f, 1.0f));
	this->pos = pos;
}

//データの解放
Field::~Field()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

//オブジェクトの更新
void Field::Update()
{
	MV1SetPosition(modelHandle, pos);
}

//オブジェクトの描画
void Field::Draw()
{
	if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
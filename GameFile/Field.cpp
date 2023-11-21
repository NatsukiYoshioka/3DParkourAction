#include"DxLib.h"
#include"GameObject.h"
#include "Field.h"

//モデルの取得と座標の初期化
Field::Field(int modelHandle, VECTOR pos)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
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

}

//オブジェクトの描画
void Field::Draw()
{

}
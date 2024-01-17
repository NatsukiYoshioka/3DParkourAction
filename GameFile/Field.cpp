#include"DxLib.h"
#include"ObjectTag.h"
#include"common.h"
#include"GameObject.h"
#include "Field.h"

//モデルの取得と座標と角度の初期化
Field::Field(int modelHandle, VECTOR pos,float angle):
	angle(initializePos)
{
	tag = ObjectTag::FIELD;
	this->modelHandle = MV1DuplicateModel(modelHandle);
	this->pos = pos;
	this->angle.y = angle;

	MV1SetRotationXYZ(this->modelHandle, this->angle);

	MV1SetPosition(this->modelHandle, this->pos);
	MV1SetupCollInfo(this->modelHandle, frameIndex, collisionDivNum, collisionDivNum, collisionDivNum);
}

//データの解放
Field::~Field()
{
	if (modelHandle != noHandle)
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
	if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
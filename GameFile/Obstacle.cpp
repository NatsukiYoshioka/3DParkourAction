#include"DxLib.h"
#include"GameObject.h"
#include"Player.h"
#include"ObjectTag.h"
#include"common.h"
#include "Obstacle.h"

const VECTOR Obstacle::scale = VGet(0.04f, 0.04f, 0.04f);
const VECTOR Obstacle::otherScale = VGet(0.2f, 0.2f, 0.2f);

//モデルの取得と座標の初期化
Obstacle::Obstacle(int modelHandle, VECTOR pos, float angle, int obstacleType):
	angle(initializePos)
{
	if (obstacleType==slideIndex)tag = ObjectTag::SLIDE_OBSTACLE;
	else if(obstacleType==otherIndex) tag = ObjectTag::OTHER_OBSTACLE;
	else tag=ObjectTag::OBSTACLE;
	
	this->modelHandle = MV1DuplicateModel(modelHandle);
	this->pos = pos;
	this->angle.y = angle;

	MV1SetRotationXYZ(this->modelHandle, this->angle);
	if (tag != ObjectTag::OTHER_OBSTACLE)MV1SetScale(this->modelHandle, scale);
	else MV1SetScale(this->modelHandle, otherScale);

	MV1SetPosition(this->modelHandle, this->pos);
	MV1SetupCollInfo(this->modelHandle, frameIndex, collisionDivNum, collisionDivNum, collisionDivNum);
}

//データの解放
Obstacle::~Obstacle()
{
	if (modelHandle != noHandle)
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
	if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
	{
		MV1DrawModel(modelHandle);
	}
}
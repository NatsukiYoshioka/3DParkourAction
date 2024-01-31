#include"DxLib.h"
#include"GameObject.h"
#include"Player.h"
#include"ObjectTag.h"
#include"common.h"
#include "Obstacle.h"

const VECTOR Obstacle::scale = VGet(0.04f, 0.04f, 0.04f);
const VECTOR Obstacle::portalScale = VGet(0.2f, 0.2f, 0.2f);
const VECTOR Obstacle::groundScale = VGet(25.0f, 25.0f, 25.0f);

//モデルの取得と座標の初期化
Obstacle::Obstacle(int modelHandle, VECTOR pos, float angle, int obstacleType):
	angle(initializePos)
{
	if (obstacleType == slideIndex)tag = ObjectTag::SLIDE_OBSTACLE;
	else if (obstacleType == portalIndex) tag = ObjectTag::PORTAL;
	else if (obstacleType == groundIndex)tag = ObjectTag::GROUND;
	else tag=ObjectTag::OBSTACLE;
	
	this->modelHandle = MV1DuplicateModel(modelHandle);
	this->pos = pos;
	this->angle.y = angle;

	MV1SetRotationXYZ(this->modelHandle, this->angle);
	
	if (tag == ObjectTag::PORTAL)MV1SetScale(this->modelHandle, portalScale);
	else if(tag==ObjectTag::GROUND)MV1SetScale(this->modelHandle, groundScale);
	else MV1SetScale(this->modelHandle, scale);

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
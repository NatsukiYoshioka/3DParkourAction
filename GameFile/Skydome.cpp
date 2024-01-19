#include"GameObject.h"
#include"ObjectTag.h"
#include"Player.h"
#include"common.h"
#include"DxLib.h"
#include"common.h"
#include "Skydome.h"

const VECTOR Skydome::scale = VGet(5.0f, 5.0f, 5.0f);

Skydome::Skydome(int modelHandle,VECTOR pos)
{
    tag = ObjectTag::SKYDOME;
    this->modelHandle = MV1DuplicateModel(modelHandle);
    this->pos = pos;
    this->pos.y = height;

    MV1SetScale(this->modelHandle, scale);

    MV1SetPosition(this->modelHandle, this->pos);
}

Skydome::~Skydome()
{
    if (modelHandle != noHandle)
    {
        MV1DeleteModel(modelHandle);
    }
}

void Skydome::Update()
{
    if (pos.x == static_cast<float>(initializeNum) && pos.z == static_cast<float>(initializeNum))
    {
        MV1SetPosition(modelHandle, VGet(Player::GetHeadPos().x, pos.y, Player::GetHeadPos().z));
    }
}

void Skydome::Draw()
{
    MV1DrawModel(modelHandle);
}
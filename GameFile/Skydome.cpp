#include"GameObject.h"
#include"ObjectTag.h"
#include"Player.h"
#include"common.h"
#include"DxLib.h"
#include"common.h"
#include "Skydome.h"

const VECTOR Skydome::scale = VGet(5.0f, 5.0f, 5.0f);

Skydome::Skydome(int modelHandle)
{
    tag = ObjectTag::SKYDOME;
    this->modelHandle = MV1DuplicateModel(modelHandle);
    pos = initializePos;
    pos.y = height;

    MV1SetScale(this->modelHandle, scale);
}

Skydome::~Skydome()
{
    if (modelHandle != -1)
    {
        MV1DeleteModel(modelHandle);
    }
}

void Skydome::Update()
{
    pos.x = Player::GetHeadPos().x;
    pos.z = Player::GetHeadPos().z;
    MV1SetPosition(modelHandle, pos);
}

void Skydome::Draw()
{
    //MV1DrawModel(modelHandle);
}
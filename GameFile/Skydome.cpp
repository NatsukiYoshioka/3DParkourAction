#include"GameObject.h"
#include"Player.h"
#include"common.h"
#include"DxLib.h"
#include"common.h"
#include "Skydome.h"

Skydome::Skydome(int modelHandle)
{
    this->modelHandle = MV1DuplicateModel(modelHandle);
    pos = initializePos;
    pos.y = 350.0f;
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
    MV1DrawModel(modelHandle);
}
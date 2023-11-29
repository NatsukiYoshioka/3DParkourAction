#include"GameObject.h"
#include"Player.h"
#include"common.h"
#include"DxLib.h"
#include "Skydome.h"

Skydome::Skydome(int modelHandle)
{
    this->modelHandle = MV1DuplicateModel(modelHandle);
    //pos = VGet(static_cast<float>(initializeNum), static_cast<float>(initializeNum), static_cast<float>(initializeNum));
    pos = VGet(960.0f, 540.0f, 0.0f);
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
    /*pos.x = Player::GetHeadPos().x;
    pos.z = Player::GetHeadPos().z;*/
    MV1SetPosition(modelHandle, pos);
}

void Skydome::Draw()
{
    MV1DrawModel(modelHandle);
}
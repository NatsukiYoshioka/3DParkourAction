#include"GameManager.h"
#include"GameObject.h"
#include"ObjectTag.h"
#include"Player.h"
#include"common.h"
#include"DxLib.h"
#include"common.h"
#include "Skydome.h"

const VECTOR Skydome::scale = VGet(5.0f, 5.0f, 5.0f);

//スカイドームの初期化
Skydome::Skydome(int modelHandle,VECTOR pos)
{
    tag = ObjectTag::SKYDOME;
    this->modelHandle = MV1DuplicateModel(modelHandle);
    this->pos = pos;
    this->pos.y = height;

    MV1SetScale(this->modelHandle, scale);

    MV1SetPosition(this->modelHandle, this->pos);
}

//データ解放
Skydome::~Skydome()
{
    if (modelHandle != noHandle)
    {
        MV1DeleteModel(modelHandle);
    }
}

//スカイドームの更新
void Skydome::Update()
{
    if (pos.x == static_cast<float>(initializeNum) && pos.z == static_cast<float>(initializeNum) && GameManager::GetGameStatus() != GameManager::SCENE::RESULT)
    {
        MV1SetPosition(modelHandle, VGet(Player::GetHeadPos().x, pos.y, Player::GetHeadPos().z));
    }
}

//スカイドーム描画
void Skydome::Draw()
{
    MV1DrawModel(modelHandle);
}
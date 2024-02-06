#include"GameManager.h"
#include"MenuScene.h"
#include"GameObject.h"
#include"ObjectTag.h"
#include"common.h"
#include "UI.h"

const float UI::maxAngle = pi1_f * cursorDimSize;

//ハンドルと座標の初期化
UI::UI(int textureHandle, VECTOR pos,int drawTiming):
    sizeX(static_cast<float>(initializeNum)),
    sizeY(static_cast<float>(initializeNum)),
    cursorAngle(static_cast<float>(initializeNum)),
    dimSize(defaultDimSize)
{
    tag = ObjectTag::UI;
    modelHandle = textureHandle;
    this->pos = pos;

    GetGraphSizeF(modelHandle, &sizeX, &sizeY);

    this->drawTiming = drawTiming;

    if (pos.z != static_cast<float>(initializeNum))
    {
        dimSize = pos.z;
    }
}

//データの解放
UI::~UI()
{
    if (modelHandle != noHandle)DeleteGraph(modelHandle);
}

//オブジェクトの更新
void UI::Update()
{
    if (static_cast<int>(pos.z) == cursorIndex)
    {
        dimSize = cursorDimSize;
        cursorAngle += rotationSpeed;
        if (cursorAngle >= maxAngle)
        {
            cursorAngle = static_cast<float>(initializeNum);
        }
        if (MenuScene::GetSelect() == MenuScene::SELECT::PLAY)
        {
            pos.x = playCursorX;
        }
        else if (MenuScene::GetSelect() == MenuScene::SELECT::TUTORIAL)
        {
            pos.x = tutorialCursorX;
        }
        else
        {
            pos.x = exitCursorX;
        }
    }
}

//オブジェクトの描画
void UI::Draw()
{
    if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
    {
        //タイトルで描画するUI
        if (drawTiming == titleIndex && GameManager::GetGameStatus() == GameManager::SCENE::TITLE)
        {
            if (static_cast<int>(pos.z) == cursorIndex)DrawRotaGraph3F(pos.x, pos.y, sizeX / cursorDimSize, sizeY / cursorDimSize, cursorScale, cursorScale, cursorAngle / DX_PI_F * pi1_f, modelHandle, TRUE);
            else if (static_cast<int>(pos.z) == titleUIIndex)DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX * titleLength, pos.y + sizeY, modelHandle, TRUE);
            else DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX / dimSize, pos.y + sizeY / dimSize, modelHandle, TRUE);
        }
        //ゲーム中に描画するUI
        if(drawTiming==inGameIndex&& GameManager::GetGameStatus() == GameManager::SCENE::GAME)DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX / dimSize, pos.y + sizeY / dimSize, modelHandle, TRUE);
        //リザルトで描画するUI
        if(drawTiming==resultIndex&& GameManager::GetGameStatus() == GameManager::SCENE::RESULT)DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX / dimSize, pos.y + sizeY / dimSize, modelHandle, TRUE);
    }
}
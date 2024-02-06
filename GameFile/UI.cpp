#include"GameManager.h"
#include"MenuScene.h"
#include"GameObject.h"
#include"ObjectTag.h"
#include"common.h"
#include "UI.h"

const float UI::maxAngle = pi1_f * cursorDimSize;

//�n���h���ƍ��W�̏�����
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

//�f�[�^�̉��
UI::~UI()
{
    if (modelHandle != noHandle)DeleteGraph(modelHandle);
}

//�I�u�W�F�N�g�̍X�V
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

//�I�u�W�F�N�g�̕`��
void UI::Draw()
{
    if (pos.x != static_cast<float>(initializeNum) || pos.y != static_cast<float>(initializeNum) || pos.z != static_cast<float>(initializeNum))
    {
        //�^�C�g���ŕ`�悷��UI
        if (drawTiming == titleIndex && GameManager::GetGameStatus() == GameManager::SCENE::TITLE)
        {
            if (static_cast<int>(pos.z) == cursorIndex)DrawRotaGraph3F(pos.x, pos.y, sizeX / cursorDimSize, sizeY / cursorDimSize, cursorScale, cursorScale, cursorAngle / DX_PI_F * pi1_f, modelHandle, TRUE);
            else if (static_cast<int>(pos.z) == titleUIIndex)DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX * titleLength, pos.y + sizeY, modelHandle, TRUE);
            else DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX / dimSize, pos.y + sizeY / dimSize, modelHandle, TRUE);
        }
        //�Q�[�����ɕ`�悷��UI
        if(drawTiming==inGameIndex&& GameManager::GetGameStatus() == GameManager::SCENE::GAME)DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX / dimSize, pos.y + sizeY / dimSize, modelHandle, TRUE);
        //���U���g�ŕ`�悷��UI
        if(drawTiming==resultIndex&& GameManager::GetGameStatus() == GameManager::SCENE::RESULT)DrawExtendGraphF(pos.x, pos.y, pos.x + sizeX / dimSize, pos.y + sizeY / dimSize, modelHandle, TRUE);
    }
}
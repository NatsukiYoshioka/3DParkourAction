#include"DxLib.h"
#include"common.h"
#include "Font.h"

//�t�H���g�̒ǉ�
Font::Font(vector<string> fontPath)
{
    this->fontPath = fontPath;
    for (int i = initializeNum; i < this->fontPath.size(); i++)
    {
        AddFontResourceEx(this->fontPath.at(i).c_str(),FR_PRIVATE,NULL);
    }
}

//�ǉ������t�H���g�̔j��
Font::~Font()
{
    for (int i = initializeNum; i < fontPath.size(); i++)
    {
        RemoveFontResourceEx(fontPath.at(i).c_str(), FR_PRIVATE, NULL);
    }
}
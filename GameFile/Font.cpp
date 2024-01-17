#include"DxLib.h"
#include"common.h"
#include "Font.h"

Font::Font(vector<string> fontPath)
{
    this->fontPath = fontPath;
    for (int i = initializeNum; i < this->fontPath.size(); i++)
    {
        AddFontResourceEx(this->fontPath.at(i).c_str(),FR_PRIVATE,NULL);
    }
}

Font::~Font()
{
    for (int i = initializeNum; i < fontPath.size(); i++)
    {
        RemoveFontResourceEx(fontPath.at(i).c_str(), FR_PRIVATE, NULL);
    }
}
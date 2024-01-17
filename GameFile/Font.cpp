#include"DxLib.h"
#include"common.h"
#include "Font.h"

Font::Font(vector<string> fontPath)
{
    for (int i = initializeNum; i < fontPath.size(); i++)
    {
        AddFontResourceEx(fontPath.at(i).c_str(),FR_PRIVATE,NULL);
    }
}

Font::~Font()
{
    
}
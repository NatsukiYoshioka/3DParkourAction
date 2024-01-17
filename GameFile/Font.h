#pragma once
#include<vector>
#include<string>

using namespace std;

/// <summary>
/// フォント管理クラス
/// </summary>
class Font
{
public:
    /// <summary>
    /// フォントデータの保存
    /// </summary>
    /// <param name="fontPath"></param>
    Font(vector<string> fontPath);

    /// <summary>
    /// フォントデータの解放
    /// </summary>
    ~Font();
private:
    vector<string> fontPath;
};

static constexpr const char* titleFontName="Moonstrike";
static constexpr const char* configFontName = "Pulse Rifle Condensed Italic";
static constexpr const char* timeFontName = "Ensign Flandry";
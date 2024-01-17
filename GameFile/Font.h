#pragma once
#include<vector>
#include<string>

using namespace std;

/// <summary>
/// �t�H���g�Ǘ��N���X
/// </summary>
class Font
{
public:
    /// <summary>
    /// �t�H���g�f�[�^�̕ۑ�
    /// </summary>
    /// <param name="fontPath"></param>
    Font(vector<string> fontPath);

    /// <summary>
    /// �t�H���g�f�[�^�̉��
    /// </summary>
    ~Font();
private:
    vector<string> fontPath;
};

static constexpr const char* titleFontName="Moonstrike";
static constexpr const char* configFontName = "Pulse Rifle Condensed Italic";
static constexpr const char* timeFontName = "Ensign Flandry";
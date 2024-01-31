#pragma once
#include"BaseScene.h"
#include<DxLib.h>

class BaseScene;
class PadInput;

/// <summary>
/// ���j���[�V�[���Ǘ��N���X
/// </summary>
class MenuScene:public BaseScene
{
public:
	/// <summary>
	/// �Q�[���ڍs�I�����
	/// </summary>
	enum class SELECT
	{
		PLAY,
		TUTORIAL,
		EXIT
	};

	MenuScene();
	~MenuScene();

	/// <summary>
	/// ���j���[�V�[���X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���͏����X�V
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// ���j���[�V�[���`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �{�^���ɕ\�����镶���̕`��
	/// </summary>
	void DrawButtonString();

	/// <summary>
	/// �^�C�g���`��
	/// </summary>
	void DrawTitleString();

	/// <summary>
	/// �I����Ԃ��擾
	/// </summary>
	/// <returns></returns>
	static SELECT GetSelect() { return select; }

	/// <summary>
	/// �I��������Ԃ��擾
	/// </summary>
	/// <returns></returns>
	static SELECT GetChoose() { return choose; }
private:
	static SELECT select;				//���j���[��ʑI�����
	static SELECT choose;				//�I���m����
	bool isChoose;				//�I���m�肵�����ǂ���

	int cooltime;
	static constexpr int maxCoolTime = 10;

	PadInput* input;			//�R���g���[���[���͏��擾�p

	static constexpr int titleFontSize = 128;
	static constexpr int buttonFontSize = 64;						//�{�^���̕����T�C�Y

	static const unsigned int buttonStringColor;					//�{�^���̕����J���[
	static const unsigned int titleStringColor;
	static const unsigned int titleStringColor2;

	static constexpr const char* titleString = "Cyber Runner";
	static constexpr int titleStringX = 300;
	static constexpr int titleStringY = 300;
	static constexpr int titleStringY2 = 305;

	static constexpr const char* playString = "PLAY";				//"PLAY"������
	static constexpr int playStringX = 440;							//PLAY��X���W

	static constexpr const char* tutorialString = "TUTORIAL";		//"TUTORIAL"������
	static constexpr int tutorialStringX = 820;						//TUTORIAL��X���W

	static constexpr const char* exitString = "EXIT";				//"EXIT"������
	static constexpr int exitStringX = 1345;						//EXIT��X���W

	static constexpr const char* menuString = "MENU";
	static constexpr int buttonStringHeight = 717;					//�{�^���̕�����Y���W
};


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
	/// �I����Ԃ��擾
	/// </summary>
	/// <returns></returns>
	static SELECT GetSelect() { return select; }
private:
	static SELECT select;				//���j���[��ʑI�����
	SELECT choose;				//�I���m����
	bool isChoose;				//�I���m�肵�����ǂ���

	PadInput* input;			//�R���g���[���[���͏��擾�p

	static constexpr int buttonFontSize = 64;						//�{�^���̕����T�C�Y

	static const unsigned int buttonStringColor;					//�{�^���̕����J���[

	static constexpr const char* playString = "PLAY";				//"PLAY"������
	static constexpr int playStringX = 445;							//PLAY��X���W

	static constexpr const char* tutorialString = "TUTORIAL";		//"TUTORIAL"������
	static constexpr int tutorialStringX = 840;						//TUTORIAL��X���W

	static constexpr const char* exitString = "EXIT";				//"EXIT"������
	static constexpr int exitStringX = 1355;						//EXIT��X���W

	static constexpr const char* menuString = "MENU";
	static constexpr int buttonStringHeight = 717;					//�{�^���̕�����Y���W
};


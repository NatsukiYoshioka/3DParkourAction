#include"FpsControl.h"
#include"Load.h"
#include"GameManager.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"

//WinMain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//--------------------------------------//
	//�����ݒ�
	//--------------------------------------//
	//DxLib������
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetWaitVSyncFlag(0);		//����������؂�

	//��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	FpsControl::CreateInstance();
	auto fpsControl = FpsControl::GetInstance();

	PadInput::CreateInstance();

	GameManager::CreateInstance();
	auto gameManager = GameManager::GetInstance();

	//--------------------------------------//
	//���C�����[�v
	//--------------------------------------//
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		//�t���[�����[�g�v�Z
		fpsControl->Update();

		//�Q�[���̍X�V
		gameManager->Update();

		//�Q�[���̕`��
		gameManager->Draw();

		//�t���[�����[�g�\��
		fpsControl->Draw();

		//�t���[�����[�g����
		fpsControl->Control();

		ScreenFlip();
	}

	//�N���X�̌㏈��
	FpsControl::DestroyInstance();
	GameManager::DestroyInstance();
	PadInput::DestroyInstance();

	//DX���C�u�����̌�n��
	DxLib_End();

	//�\�t�g�̏I��
	return 0;
}
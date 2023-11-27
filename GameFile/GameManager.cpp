#include"BaseScene.h"
#include"MenuScene.h"
#include"GameScene.h"
#include"ResultScene.h"
#include"GameObjectManager.h"
#include"DxLib.h"
#include <cstddef>
#include "GameManager.h"

GameManager* GameManager::sceneManager = nullptr;
BaseScene* GameManager::nowScene = NULL;

//�V�[���̏������ƃI�u�W�F�N�g�̐���
GameManager::GameManager() :
	sceneStatus(SCENE::TITLE)
{
	GameObjectManager::CreateInstance();
	gameObjectManager = GameObjectManager::GetInstance();
	gameObjectManager->InitObject();

	nowScene = new MenuScene();
}

//�N���X�̌㏈��
GameManager::~GameManager()
{
	GameObjectManager::DestroyInstance();
}

//�C���X�^���X����
void GameManager::CreateInstance()
{
	if (!sceneManager)
	{
		sceneManager = new GameManager();
	}
}

//�C���X�^���X�j��
void GameManager::DestroyInstance()
{
	if (sceneManager)
	{
		delete(sceneManager);
	}
}

//�V�[���������ɂ���ĕς���֐�
void GameManager::ChangeScene(SCENE scene)
{
	if (nowScene != NULL)
	{
		delete nowScene;
	}

	sceneStatus = scene;

	switch (scene)
	{
	case SCENE::TITLE:
		nowScene = new MenuScene();
		break;
	case SCENE::GAME:
		nowScene = new GameScene();
		break;
	case SCENE::RESULT:
		nowScene = new ResultScene();
		break;
	}
}

//���݂̃V�[���̍X�V
void GameManager::Update()
{
	gameObjectManager->Update();
	nowScene->Update();

	if (CheckHitKey(KEY_INPUT_RETURN) != 0)
	{
		ChangeScene(SCENE::GAME);
	}
}

//���݂̃V�[���̕`��
void GameManager::Draw()
{
	gameObjectManager->Draw();
	nowScene->Draw();
}
#include"BaseScene.h"
#include"GameObjectManager.h"
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
	gameObjectManager->AddObject();
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

		break;
	case SCENE::GAME:

		break;
	case SCENE::RESULT:

		break;
	}
}

//���݂̃V�[���̍X�V
void GameManager::Update()
{
	gameObjectManager->Update();
	nowScene->Update();
}

//���݂̃V�[���̕`��
void GameManager::Draw()
{
	gameObjectManager->Draw();
	nowScene->Draw();
}
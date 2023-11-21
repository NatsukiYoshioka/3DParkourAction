#include"BaseScene.h"
#include"GameObjectManager.h"
#include <cstddef>
#include "GameManager.h"

GameManager* GameManager::sceneManager = nullptr;
BaseScene* GameManager::nowScene = NULL;

//シーンの初期化とオブジェクトの生成
GameManager::GameManager() :
	sceneStatus(SCENE::TITLE)
{
	GameObjectManager::CreateInstance();
	gameObjectManager = GameObjectManager::GetInstance();
	gameObjectManager->AddObject();
}

//クラスの後処理
GameManager::~GameManager()
{
	GameObjectManager::DestroyInstance();
}

//インスタンス生成
void GameManager::CreateInstance()
{
	if (!sceneManager)
	{
		sceneManager = new GameManager();
	}
}

//インスタンス破棄
void GameManager::DestroyInstance()
{
	if (sceneManager)
	{
		delete(sceneManager);
	}
}

//シーンを引数によって変える関数
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

//現在のシーンの更新
void GameManager::Update()
{
	gameObjectManager->Update();
	nowScene->Update();
}

//現在のシーンの描画
void GameManager::Draw()
{
	gameObjectManager->Draw();
	nowScene->Draw();
}
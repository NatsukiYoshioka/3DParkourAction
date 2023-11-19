#include"GameObject.h"
#include<vector>
#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::gameObjectManager = nullptr;

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}

void GameObjectManager::CreateInstance()
{
	if (!gameObjectManager)
	{
		gameObjectManager = new GameObjectManager();
	}
}
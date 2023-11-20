#include<vector>
#include<string>
#include"Load.h"
#include"GameObject.h"
#include"Player.h"
#include"common.h"
#include "GameObjectManager.h"
using namespace std;

GameObjectManager* GameObjectManager::gameObjectManager = nullptr;
const string GameObjectManager::dataFilePath = "data/pathfile/data.csv";

//データのロードとオブジェクトの生成
GameObjectManager::GameObjectManager()
{
	
}

//データの解放
GameObjectManager::~GameObjectManager()
{

}

//インスタンスの生成
void GameObjectManager::CreateInstance()
{
	if (!gameObjectManager)
	{
		gameObjectManager = new GameObjectManager();
	}
}

//インスタンスの破棄
void GameObjectManager::DestroyInstance()
{
	if (gameObjectManager)
	{
		delete(gameObjectManager);
	}
}

//データのロードとインスタンスの追加
void GameObjectManager::AddObject()
{
	Load::CreateInstance();
	load = Load::GetInstance();
	load->ReadFile(dataFilePath, true, true);

	objectInstance.push_back(new Player(load->GetPlayerModelHandle()));
}

//オブジェクト全体の更新
void GameObjectManager::Update()
{

}

//オブジェクト全体の描画
void GameObjectManager::Draw()
{

}
#include<vector>
#include<string>
#include"Load.h"
#include"GameObject.h"
#include"Player.h"
#include"Field.h"
#include"Obstacle.h"
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

	//プレイヤーオブジェクトの追加
	objectInstance.push_back(new Player(load->GetPlayerModelHandle(),load->GetPlayerAnimationHandle()));

	//フィールドオブジェクトの追加
	for (int i = initializeNum; i < load->GetFieldModelHandle().size(); i++)
	{
		objectInstance.push_back(new Field(load->GetFieldModelHandle().at(i), load->GetFieldPos().at(i)));
	}

	//障害物オブジェクトの追加
	for (int i = initializeNum; i < load->GetObstacleModelHandle().size(); i++)
	{
		objectInstance.push_back(new Obstacle(load->GetObstacleModelHandle().at(i), load->GetObstaclePos().at(i)));
	}
}

//オブジェクト全体の更新
void GameObjectManager::Update()
{

}

//オブジェクト全体の描画
void GameObjectManager::Draw()
{

}
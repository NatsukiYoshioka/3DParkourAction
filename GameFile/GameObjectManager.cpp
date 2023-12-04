#include<vector>
#include<string>
#include"Load.h"
#include"GameObject.h"
#include"Player.h"
#include"Camera.h"
#include"Field.h"
#include"Obstacle.h"
#include"Skydome.h"
#include"common.h"
#include "GameObjectManager.h"
using namespace std;

GameObjectManager* GameObjectManager::gameObjectManager = nullptr;
const string GameObjectManager::dataFilePath = "data/file/data.csv";

//データのロード
GameObjectManager::GameObjectManager()
{
	Load::CreateInstance();
	load = Load::GetInstance();
	load->ReadFile(dataFilePath, true, true);
	load->LoadData();
}

//データの解放
GameObjectManager::~GameObjectManager()
{
	for (int i = initializeNum; i < objectInstance.size(); i++)
	{
		delete(objectInstance.at(i));
	}
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
	Load::DestroyInstance();
	if (gameObjectManager)
	{
		delete(gameObjectManager);
	}
}

//インスタンスの初期化
void GameObjectManager::InitObject()
{
	//オブジェクトが追加されていたら一度初期化する
	if (!objectInstance.empty())
	{
		objectInstance.clear();
	}

	//プレイヤーオブジェクトの追加
	objectInstance.push_back(new Player(load->GetPlayerModelHandle(),load->GetPlayerAnimationHandle()));

	//カメラの追加
	objectInstance.push_back(new Camera());

	//フィールドオブジェクトの追加
	for (int i = initializeNum; i < load->GetFieldModelHandle().size(); i++)
	{
		objectInstance.push_back(new Field(load->GetFieldModelHandle().at(i), load->GetFieldPos().at(i), load->GetFieldAngle().at(i)));
	}

	//障害物オブジェクトの追加
	for (int i = initializeNum; i < load->GetObstacleModelHandle().size(); i++)
	{
		objectInstance.push_back(new Obstacle(load->GetObstacleModelHandle().at(i), load->GetObstaclePos().at(i)));
	}

	//スカイドームの追加
	for (int i = initializeNum; i < load->GetSkydomeModelHandle().size(); i++)
	{
		objectInstance.push_back(new Skydome(load->GetSkydomeModelHandle().at(i)));
	}
}

//オブジェクト全体の更新
void GameObjectManager::Update()
{
	for (int i = initializeNum; i < objectInstance.size(); i++)
	{
		objectInstance.at(i)->Update();
	}
}

//オブジェクト全体の描画
void GameObjectManager::Draw()
{
	for (int i = initializeNum; i < objectInstance.size(); i++)
	{
		objectInstance.at(i)->Draw();
	}
}
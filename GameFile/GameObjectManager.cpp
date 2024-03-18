#include<vector>
#include<string>
#include"Load.h"
#include"Font.h"
#include"GameObject.h"
#include"ObjectTag.h"
#include"Player.h"
#include"Camera.h"
#include"Field.h"
#include"Obstacle.h"
#include"Skydome.h"
#include"UI.h"
#include"ObjectTag.h"
#include"common.h"
#include "GameObjectManager.h"
using namespace std;

GameObjectManager* GameObjectManager::gameObjectManager = nullptr;
const string GameObjectManager::dataFilePath = "data/file/data.csv";

//データのロード
GameObjectManager::GameObjectManager():
	font(nullptr)
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
	if(font)delete(font);
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
		objectInstance.push_back(new Obstacle(load->GetObstacleModelHandle().at(i), load->GetObstaclePos().at(i), load->GetObstacleAngle().at(i), load->GetObstacleType().at(i)));
	}

	//スカイドームの追加
	for (int i = initializeNum; i < load->GetSkydomeModelHandle().size(); i++)
	{
		objectInstance.push_back(new Skydome(load->GetSkydomeModelHandle().at(i), load->GetSkydomePos().at(i)));
	}

	//UIの追加
	for (int i = initializeNum; i < load->GetUITextureHandle().size(); i++)
	{
		objectInstance.push_back(new UI(load->GetUITextureHandle().at(i), load->GetUIPos().at(i),load->GetUIDrawTiming().at(i)));
	}

	//フォントデータの追加
	font=new Font(load->GetFontPath());
}

//オブジェクト全体の更新
void GameObjectManager::Update()
{
	for (int i = initializeNum; i < objectInstance.size(); i++)
	{
		objectInstance.at(i)->Update();
		for (int j = initializeNum; j < objectInstance.size(); j++)
		{
			//当たり判定更新(距離が遠い場合は処理しない)
			if (i != j)
			{
				if ((objectInstance.at(j)->GetObjectTag() == ObjectTag::FIELD && maxObjectDistance * maxObjectDistance >= (objectInstance.at(i)->GetPos().x - objectInstance.at(j)->GetPos().x) * (objectInstance.at(i)->GetPos().x - objectInstance.at(j)->GetPos().x) + (objectInstance.at(i)->GetPos().y - objectInstance.at(j)->GetPos().y) * (objectInstance.at(i)->GetPos().y - objectInstance.at(j)->GetPos().y) + (objectInstance.at(i)->GetPos().z - objectInstance.at(j)->GetPos().z) * (objectInstance.at(i)->GetPos().z - objectInstance.at(j)->GetPos().z)) || ((objectInstance.at(j)->GetObjectTag() == ObjectTag::OBSTACLE || objectInstance.at(j)->GetObjectTag() == ObjectTag::SLIDE_OBSTACLE) && maxObstacleDistance * maxObstacleDistance >= (objectInstance.at(i)->GetPos().x - objectInstance.at(j)->GetPos().x) * (objectInstance.at(i)->GetPos().x - objectInstance.at(j)->GetPos().x) + (objectInstance.at(i)->GetPos().y - objectInstance.at(j)->GetPos().y) * (objectInstance.at(i)->GetPos().y - objectInstance.at(j)->GetPos().y) + (objectInstance.at(i)->GetPos().z - objectInstance.at(j)->GetPos().z) * (objectInstance.at(i)->GetPos().z - objectInstance.at(j)->GetPos().z)))objectInstance.at(i)->OnCollisionEnter(objectInstance.at(j), objectInstance.at(j)->GetObjectTag());
			}
		}
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
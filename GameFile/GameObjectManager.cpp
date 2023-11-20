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

//�f�[�^�̃��[�h�ƃI�u�W�F�N�g�̐���
GameObjectManager::GameObjectManager()
{
	
}

//�f�[�^�̉��
GameObjectManager::~GameObjectManager()
{

}

//�C���X�^���X�̐���
void GameObjectManager::CreateInstance()
{
	if (!gameObjectManager)
	{
		gameObjectManager = new GameObjectManager();
	}
}

//�C���X�^���X�̔j��
void GameObjectManager::DestroyInstance()
{
	if (gameObjectManager)
	{
		delete(gameObjectManager);
	}
}

//�f�[�^�̃��[�h�ƃC���X�^���X�̒ǉ�
void GameObjectManager::AddObject()
{
	Load::CreateInstance();
	load = Load::GetInstance();
	load->ReadFile(dataFilePath, true, true);

	objectInstance.push_back(new Player(load->GetPlayerModelHandle()));
}

//�I�u�W�F�N�g�S�̂̍X�V
void GameObjectManager::Update()
{

}

//�I�u�W�F�N�g�S�̂̕`��
void GameObjectManager::Draw()
{

}
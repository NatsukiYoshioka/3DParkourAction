#pragma once

using namespace std;

class GameObject;

/// <summary>
/// ゲームオブジェクト管理クラス
/// </summary>
class GameObjectManager
{
private:
	GameObjectManager();
	~GameObjectManager();
	
public:
	/// <summary>
	/// インスタンスが一度も生成されていなかったらインスタンスを生成する
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static GameObjectManager* GetInstance() { gameObjectManager; }

private:
	static GameObjectManager* gameObjectManager;		//ゲームオブジェクト管理クラスのインスタンス
	vector<GameObject*> objectInstance;					//オブジェクトのインスタンス
};


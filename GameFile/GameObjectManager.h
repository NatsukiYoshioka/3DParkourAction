#pragma once

using namespace std;

class Load;
class GameObject;

/// <summary>
/// ゲームオブジェクト管理クラス
/// </summary>
class GameObjectManager
{
private:
	/// <summary>
	/// データのロードとオブジェクトの生成
	/// </summary>
	GameObjectManager();

	/// <summary>
	/// データの解放
	/// </summary>
	~GameObjectManager();
	
	/// <summary>
	/// オブジェクト全体の更新
	/// </summary>
	void Update();

	/// <summary>
	/// オブジェクト全体の描画
	/// </summary>
	void Draw();
public:
	/// <summary>
	/// インスタンスが一度も生成されていなかったらインスタンスを生成する
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンスの破棄
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static GameObjectManager* GetInstance() { gameObjectManager; }

private:
	static GameObjectManager* gameObjectManager;		//ゲームオブジェクト管理クラスのインスタンス
	Load* load;											//ロードクラス
	static const string dataFilePath;					//データ格納ファイルのパス

	vector<GameObject*> objectInstance;					//オブジェクトのインスタンス
};


#pragma once
#include<string>
#include<vector>

using namespace std;

class Load;
class Font;
class GameObject;

/// <summary>
/// ゲームオブジェクト管理クラス
/// </summary>
class GameObjectManager
{
private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameObjectManager();

	/// <summary>
	/// データの解放
	/// </summary>
	~GameObjectManager();
	
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
	static GameObjectManager* GetInstance() { return gameObjectManager; }

	/// <summary>
	/// オブジェクトの初期化
	/// </summary>
	void InitObject();

	/// <summary>
	/// オブジェクト全体の更新
	/// </summary>
	void Update();

	/// <summary>
	/// オブジェクト全体の描画
	/// </summary>
	void Draw();

private:
	static GameObjectManager* gameObjectManager;		//ゲームオブジェクト管理クラスのインスタンス
	Load* load;											//ロードクラス
	Font* font;											//フォントクラス
	static const string dataFilePath;					//データ格納ファイルのパス

	vector<GameObject*> objectInstance;					//オブジェクトのインスタンス
	static constexpr int playerIndex = 1;				//プレイヤーインスタンスが格納されている場所

	static constexpr float maxObjectDistance = 1000.0f;	//当たり判定を行う距離
	static constexpr float maxObstacleDistance = 100.0f;//当たり判定を行う障害物との距離
};


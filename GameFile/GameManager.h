#pragma once

class BaseScene;
class GameObjectManager;
class PadInput;

/// <summary>
/// ゲーム全体の管理をするクラス
/// </summary>
class GameManager
{
private:
	/// <summary>
	/// シーンの初期化とオブジェクトの生成
	/// </summary>
	GameManager();

	/// <summary>
	/// クラスの後処理
	/// </summary>
	~GameManager();

public:
	/// <summary>
	/// シーンの状態を管理
	/// </summary>
	enum class SCENE
	{
		TITLE,								//タイトル画面
		GAME,								//ゲーム画面
		RESULT								//リザルト画面
	};

	/// <summary>
	/// インスタンス生成
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンス破棄
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static GameManager* GetInstance() { return sceneManager; }

	/// <summary>
	/// シーンを引数によって変える関数
	/// </summary>
	/// <param name="scene">変更するシーン</param>
	void ChangeScene(SCENE scene);

	/// <summary>
	/// 現在のシーンの更新
	/// </summary>
	void Update();

	/// <summary>
	/// 現在のシーンの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// シーンの状態を取得
	/// </summary>
	/// <returns>シーンの状態</returns>
	SCENE GetGameStatus() { return sceneStatus; }

private:
	static GameManager* sceneManager;			//クラスのインスタンス
	static BaseScene* nowScene;					//現在のシーン
	SCENE sceneStatus;							//シーンの状態

	GameObjectManager* gameObjectManager;		//ゲームオブジェクト管理クラス
	PadInput* input;
};


#pragma once

using namespace std;

/// <summary>
/// ゲームに必要なデータをロードするクラス
/// </summary>
class Load
{
private:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Load();

	/// <summary>
	/// 格納したデータの解放
	/// </summary>
	~Load();

public:
	/// <summary>
	/// インスタンスの生成
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// インスタンスの破棄
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// インスタンス取得
	/// </summary>
	/// <returns>クラスのインスタンス</returns>
	static Load* GetInstance() { return load; }

	/// <summary>
	/// ファイルからデータのパスを取得
	/// </summary>
	/// <param name="filepath">csvファイルのパス</param>
	/// <param name="isHeader">ヘッダーがあるかどうか</param>
	/// <param name="isIndex">インデックスがあるかどうか</param>
	void ReadFile(string filepath, bool isHeader, bool isIndex);

	/// <summary>
	/// データのロード
	/// </summary>
	void LoadData();

	/// <summary>
	/// プレイヤーのモデルハンドル取得
	/// </summary>
	/// <returns>プレイヤーモデルハンドル</returns>
	int GetPlayerModelHandle() { return playerModelHandle; }

	/// <summary>
	/// フィールドのモデルハンドル取得
	/// </summary>
	/// <returns>フィールドモデルハンドル</returns>
	vector<int> GetFieldModelHandle() { return fieldModelHandle; }

	/// <summary>
	/// 障害物のモデルハンドル取得
	/// </summary>
	/// <returns>障害物のモデルハンドル</returns>
	vector<int> GetObstacleModelHandle() { return obstacleModelHandle; }

private:
	static Load* load;					//ロードクラスのインスタンス

	string filePath;					//ゲームに必要なデータのパスが入ったファイルのパス
	bool isHeader;						//ヘッダーがあるかどうか
	bool isIndex;						//インデックスがあるかどうか
	static constexpr char delim = ',';	//区切りの文字

	vector<string> header;				//ヘッダー名保管
	vector<string> index;				//インデックス名保管
	vector<vector<string>> cell;		//要素保管

	int playerModelHandle;				//プレイヤーのモデルハンドル
	vector<int> fieldModelHandle;		//フィールドのモデルハンドル
	vector<int> obstacleModelHandle;	//障害物のモデルハンドル
};


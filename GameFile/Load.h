#pragma once
#include<string>
#include<vector>
#include<DxLib.h>

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
	/// プレイヤーのアニメーション取得
	/// </summary>
	/// <returns>アニメーションのvector配列</returns>
	vector<int> GetPlayerAnimationHandle() { return playerAnimationHandle; }

	/// <summary>
	/// フィールドのモデルハンドル取得
	/// </summary>
	/// <returns>フィールドモデルハンドルのvector配列</returns>
	vector<int> GetFieldModelHandle() { return fieldModelHandle; }

	/// <summary>
	/// フィールドの座標取得
	/// </summary>
	/// <returns>フィールド座標のvector配列</returns>
	vector<VECTOR> GetFieldPos() { return fieldPos; }

	/// <summary>
	/// 障害物のモデルハンドル取得
	/// </summary>
	/// <returns>障害物のモデルハンドルのvector配列</returns>
	vector<int> GetObstacleModelHandle() { return obstacleModelHandle; }

	/// <summary>
	/// 障害物の座標取得
	/// </summary>
	/// <returns>障害物の座標のvector配列</returns>
	vector<VECTOR> GetObstaclePos() { return obstaclePos; }

private:
	static Load* load;				//ロードクラスのインスタンス

	string filePath;					//ゲームに必要なデータのパスが入ったファイルのパス
	bool isHeader;						//ヘッダーがあるかどうか
	bool isIndex;						//インデックスがあるかどうか
	static constexpr char delim = ',';	//区切りの文字

	vector<string> header;				//ヘッダー名保管
	vector<string> index;				//インデックス名保管
	vector<vector<string>> cell;		//要素保管

	int playerModelHandle;				//プレイヤーのモデルハンドル
	vector<int> playerAnimationHandle;	//プレイヤーのアニメーションハンドル

	vector<int> fieldModelHandle;		//フィールドのモデルハンドル
	vector<VECTOR> fieldPos;			//フィールドモデルの各座標

	vector<int> obstacleModelHandle;	//障害物のモデルハンドル
	vector<VECTOR> obstaclePos;			//障害物の各座標

	static constexpr const char* playerHeader = "PLAYER";
	static constexpr const char* animationHeader = "ANIMATION";
	static constexpr const char* fieldHeader = "FIELD";
	static constexpr const char* fieldPosXHeader = "FieldPosX";
	static constexpr const char* obstacleHeader = "OBSTACLE";
	static constexpr const char* obstaclePosXHeader = "ObstaclePosX";
};


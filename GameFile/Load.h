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
	/// フィールドの角度取得
	/// </summary>
	/// <returns>フィールド角度のvector配列</returns>
	vector<float> GetFieldAngle() { return fieldAngle; }

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

	/// <summary>
	/// 障害物の角度取得
	/// </summary>
	/// <returns>障害物の角度のvector配列</returns>
	vector<float> GetObstacleAngle() { return obstacleAngle; }

	/// <summary>
	/// 障害物がくぐれるかどうか取得
	/// </summary>
	/// <returns>障害物がくぐれるかどうか</returns>
	vector<int> GetObstacleType() { return obstacleType; }

	/// <summary>
	/// スカイドームのモデルハンドル取得
	/// </summary>
	/// <returns>スカイドームのモデルハンドルのvector配列</returns>
	vector<int> GetSkydomeModelHandle() { return skydomeModelHandle; }

	/// <summary>
	/// スカイドームの座標取得
	/// </summary>
	/// <returns>スカイドーム座標のvector配列</returns>
	vector<VECTOR> GetSkydomePos() { return skydomePos; }

	/// <summary>
	/// UIテクスチャハンドルの取得
	/// </summary>
	/// <returns>UIテクスチャハンドルのvector配列</returns>
	vector<int> GetUITextureHandle() { return UITextureHandle; }

	/// <summary>
	/// UIの座標取得
	/// </summary>
	/// <returns>UI座標のvector配列</returns>
	vector<VECTOR> GetUIPos() { return UIPos; }

	/// <summary>
	/// UIを描画するタイミングを取得
	/// </summary>
	/// <returns>UIを描画するタイミングを保存したvector配列</returns>
	vector<int> GetUIDrawTiming() { return UIDrawTiming; }

	/// <summary>
	/// フォントパス取得
	/// </summary>
	/// <returns>フォントパスのvector配列</returns>
	vector<string> GetFontPath(){return fontPath;}

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
	int tempFieldModelHandle;			//フィールドモデル複数追加用仮保存
	vector<VECTOR> fieldPos;			//フィールドモデルの各座標
	vector<float> fieldAngle;			//フィールドモデルの角度

	vector<int> obstacleModelHandle;	//障害物のモデルハンドル
	int tempObstacleModelHandle;		//障害物モデル複数追加用仮保存
	vector<VECTOR> obstaclePos;			//障害物の各座標
	vector<float> obstacleAngle;		//障害物の角度
	vector<int> obstacleType;			//障害物の種類

	vector<int> skydomeModelHandle;		//スカイドームのモデルハンドル
	vector<VECTOR> skydomePos;			//スカイドームのポジション

	vector<int> UITextureHandle;		//UI画像ハンドル
	int tempUITextureHandle;			//UI仮保存用ハンドル
	vector<VECTOR> UIPos;				//UI座標
	vector<int> UIDrawTiming;			//UIを描画するタイミング

	vector<string> fontPath;            //フォントパス

	//外部ファイル内のヘッダー名
	static constexpr const char* playerHeader = "PLAYER";
	static constexpr const char* animationHeader = "ANIMATION";
	static constexpr const char* fieldHeader = "FIELD";
	static constexpr const char* fieldPosXHeader = "FieldPosX";
	static constexpr const char* fieldAngleHeader = "FieldAngle";
	static constexpr const char* obstacleHeader = "OBSTACLE";
	static constexpr const char* obstaclePosXHeader = "ObstaclePosX";
	static constexpr const char* obstacleAngleHeader = "ObstacleAngle";
	static constexpr const char* obstacleObstacleTypeHeader = "ObstacleType";
	static constexpr const char* skydomeHeader = "SKYDOME";
	static constexpr const char* skydomePosXHeader = "SkydomePosX";
	static constexpr const char* UIHeader = "UI";
	static constexpr const char* UIPosXHeader = "UIPosX";
	static constexpr const char* UIDrawTimingHeader = "DrawTiming";
	static constexpr const char* fontHeader="FONT";
};


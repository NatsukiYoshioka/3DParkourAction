#pragma once

/// <summary>
/// シングルトンパターンのFPS制御クラス
/// </summary>
class FpsControl
{
private:
	/// <summary>
	/// カウントの初期化
	/// </summary>
	FpsControl();

	/// <summary>
	/// クラス後処理
	/// </summary>
	~FpsControl() {}
public:
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
	/// <returns>クラス変数</returns>
	static FpsControl* GetInstance() { return fpsControl; }

	/// <summary>
	/// フレームレート計算
	/// </summary>
	void Update();

	/// <summary>
	/// FPS表示
	/// </summary>
	void Draw();

	/// <summary>
	/// フレームレート制御
	/// </summary>
	void Control();

private:
	static FpsControl* fpsControl;	//クラス変数
	int startTime;					//測定開始時刻
	int count;						//カウンタ
	float nowFps;					//現在のFps
	const int sampleAvg = 60;		//平均を取るサンプル数
	const int FPS = 60;				//設定したFPS

	static constexpr int fpsX = 0;							//FPSを表示するX座標
	static constexpr int fpsY = 0;							//FPSを表示するY座標
	static const unsigned int blueColor;					//青色を保持する定数
	static constexpr const char* valueString = "%.1f";		//FPS値を表示する文字列
};


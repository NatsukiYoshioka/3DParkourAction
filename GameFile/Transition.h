#pragma once

class Transition
{
private:
	/// <summary>
	/// 画像のロード
	/// </summary>
	Transition();

	/// <summary>
	/// データ破棄
	/// </summary>
	~Transition();
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
	/// <returns>クラスのインスタンス</returns>
	static Transition* GetInstance() { return transition; }

	/// <summary>
	/// 白画像の透過率設定
	/// </summary>
	/// <param name="transRate">透過率</param>
	static void UpdateWhiteTransition(float transRate);

	/// <summary>
	/// 黒画像の透過率設定
	/// </summary>
	/// <param name="transRate">透過率</param>
	static void UpdateBlackTransition(float transRate);

	/// <summary>
	/// 画像の描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 白画像透過率取得
	/// </summary>
	/// <returns>白画像透過率</returns>
	static float GetWhiteTransRate() { return whiteTransRate; }

	/// <summary>
	/// 黒画像透過率取得
	/// </summary>
	/// <returns>黒画像透過率</returns>
	static float GetBlackTransRate() { return blackTransRate; }
private:
	static Transition* transition;			//クラスのインスタンス

	static float whiteTransRate;			//白画像の透過率
	static float blackTransRate;			//黒画像の透過率

	static constexpr float maxTransRate = 1.0f;

	static constexpr float maxFade = 255;	//最大透過率

	int whiteTextureHandle;					//白画像ハンドル
	int blackTextureHandle;					//黒画像ハンドル

	static constexpr int texturePosX1 = 0;	//描画する範囲座標
	static constexpr int texturePosX2 = 1920;
	static constexpr int texturePosY1 = -5;
	static constexpr int texturePosY2 = 1080;

	static constexpr const char* whiteTexturePath = "data/UI/white.png";	//画像のパス
	static constexpr const char* blackTexturePath = "data/UI/black.png";
};


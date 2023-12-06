#pragma once
#include"ObjectTag.h"
#include"DxLib.h"

/// <summary>
/// 全てのゲームオブジェクトの基底クラス
/// </summary>
class GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameObject();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameObject();

	//純粋仮想関数
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//オブジェクトの当たり判定
	virtual void OnCollisionEnter(GameObject* other, const ObjectTag tag) {}

	//モデルの取得
	virtual int GetModelHandle() = 0;
	//タグの取得
	virtual ObjectTag GetObjectTag() = 0;
	//座標の取得
	virtual VECTOR GetPos() = 0;
protected:
	ObjectTag tag;				//オブジェクトのタグ
	int modelHandle;			//モデルのハンドル
	VECTOR pos;					//オブジェクトの座標
};


#include"GameObject.h"
#include"DxLib.h"
#include "Player.h"

//オブジェクトの初期化
Player::Player(int modelHandle, vector<int> animationHandle)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	pos = VGet(0.0f, 0.0f, 0.0f);

	this->animationHandle = animationHandle;
	//プレイヤーの初期状態をしゃがみにする
	status = STATUS::CROUCH;
}

//データの解放
Player::~Player()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

//オブジェクトの更新
void Player::Update()
{

}

//オブジェクトの描画
void Player::Draw()
{

}
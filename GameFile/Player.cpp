#include"GameObject.h"
#include"DxLib.h"
#include "Player.h"

VECTOR Player::headPos = VGet(0.0f, 0.0f, 0.0f);

//オブジェクトの初期化
Player::Player(int modelHandle, vector<int> animationHandle)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
	pos = VGet(960.0f, 0.0f, 0.0f);

	MV1SetScale(this->modelHandle, VGet(5.0f, 5.0f, 5.0f));
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
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	MV1SetPosition(modelHandle, pos);
}

//オブジェクトの描画
void Player::Draw()
{
	//MV1DrawModel(modelHandle);
}
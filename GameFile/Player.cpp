#include"GameObject.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

VECTOR Player::headPos = VGet(0.0f, 0.0f, 0.0f);

//オブジェクトの初期化
Player::Player(int modelHandle, vector<int> animationHandle):
	input(nullptr)
{
	//クラスのインスタンス取得
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	pos = VGet(960.0f, 540.0f, -200.0f);

	//MV1SetScale(this->modelHandle, VGet(1.0f, 1.0f, 1.0f));
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
	UpdateInput();
	MV1SetPosition(modelHandle, pos);
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
}

void Player::UpdateInput()
{
	//左スティック左倒し
	if (input->GetInput().ThumbLX < initializeNum)
	{
		pos.x -= moveSpeed;
	}
	//左スティック右倒し
	if (input->GetInput().ThumbLX > initializeNum)
	{
		pos.x += moveSpeed;
	}
	//左スティック上倒し
	if (input->GetInput().ThumbLY < initializeNum)
	{
		pos.z += moveSpeed;
	}
	//左スティック下倒し
	if (input->GetInput().ThumbLY > initializeNum)
	{
		pos.z -= moveSpeed;
	}
}

//オブジェクトの描画
void Player::Draw()
{
	MV1DrawModel(modelHandle);
}
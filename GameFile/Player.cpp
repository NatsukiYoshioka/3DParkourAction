#include"GameObject.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

VECTOR Player::headPos = initializePos;
VECTOR Player::angle = initializePos;
const VECTOR Player::fixAngle= VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f);

//オブジェクトの初期化
Player::Player(int modelHandle, vector<int> animationHandle):
	input(nullptr),
	addMove({ static_cast<int>(initializeNum) })
{
	//クラスのインスタンス取得
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	pos = VGet(960.0f, 540.0f, -200.0f);

	MV1SetRotationXYZ(this->modelHandle, fixAngle);

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
	MV1SetRotationXYZ(modelHandle, VGet(angle.x, angle.y + fixAngle.y, angle.z));
	MV1SetPosition(modelHandle, pos);
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
}

void Player::UpdateInput()
{
	//視点移動入力処理
	//右スティック左倒し
	if (input->GetInput().ThumbRX < initializeNum || CheckHitKey(KEY_INPUT_LEFT) != initializeNum)
	{
		angle.y -= directionSpeed;
	}
	//右スティック右倒し
	if (input->GetInput().ThumbRX > initializeNum || CheckHitKey(KEY_INPUT_RIGHT) != initializeNum)
	{
		angle.y += directionSpeed;
	}

	//移動入力処理
	//左スティック左倒し
	if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
	{
		addMove= VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VCross(addMove, VGet(0.0f, 1.0f, 0.0f));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));
	}
	//左スティック右倒し
	if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VCross(addMove, VGet(0.0f, 1.0f, 0.0f));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));
	}
	//左スティック上倒し
	if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));
	}
	//左スティック下倒し
	if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));
	}
}

//オブジェクトの描画
void Player::Draw()
{
	MV1DrawModel(modelHandle);
}
#include"GameObject.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

const VECTOR Player::scale = VGet(0.125f, 0.125f, 0.125f);
const unsigned int Player::capsuleColor = GetColor(255, 255, 0);
VECTOR Player::headPos = initializePos;
VECTOR Player::angle = initializePos;
const VECTOR Player::fixAngle= VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f);

//オブジェクトの初期化
Player::Player(int modelHandle, vector<int> animationHandle):
	input(nullptr),
	addMove(initializePos),
	status(STATUS::STAND),
	animationIndex(initializeNum),
	totalAnimTime(static_cast<float>(initializeNum)),
	playAnimTime(static_cast<float>(initializeNum)),
	headTopPos(initializePos),
	toePos(initializePos)
{
	//クラスのインスタンス取得
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	MV1SetScale(this->modelHandle, scale);
	pos = VGet(960.0f, 200.0f, -200.0f);

	MV1SetRotationXYZ(this->modelHandle, fixAngle);

	this->animationHandle = animationHandle;

	//プレイヤーの初期状態を立ち状態にする
	animationIndex = MV1AttachAnim(this->modelHandle, initializeNum, this->animationHandle.at(static_cast<int>(status)));
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
	UpdateAnimation();
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	//当たり判定用カプセル座標の計算
	headTopPos = MV1GetFramePosition(modelHandle, headTopFrameIndex);
	toePos = MV1GetFramePosition(modelHandle, toeFrameIndex);
	toePos.x = headTopPos.x;
	toePos.z = headTopPos.z;
	toePos.y += fixToePosY;
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

	status = STATUS::STAND;

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

		status = STATUS::RUN_LEFT;
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

		status = STATUS::RUN_RIGHT;
	}
	//左スティック上倒し
	if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

		status = STATUS::RUN;
	}
	//左スティック下倒し
	if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
	{
		addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		addMove = VNorm(addMove);
		addMove = VScale(addMove, moveSpeed);
		pos = VAdd(pos, addMove);
		addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

		status = STATUS::RUN_BACK;
	}
}

//アニメーションの更新
void Player::UpdateAnimation()
{
	//アニメーションのアタッチ
	MV1DetachAnim(modelHandle, animationIndex);
	animationIndex = MV1AttachAnim(modelHandle, initializeNum, animationHandle.at(static_cast<int>(status)));
	//アニメーションの再生
	totalAnimTime = MV1GetAttachAnimTotalTime(modelHandle, animationIndex);
	playAnimTime += animationSpeed;
	if (playAnimTime >= totalAnimTime)
	{
		playAnimTime = static_cast<float>(initializeNum);
	}
	MV1SetAttachAnimTime(modelHandle, animationIndex, playAnimTime);
}

//当たり判定
void Player::OnCollisionEnter(const GameObject* other)
{

}

//オブジェクトの描画
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	//当たり判定デバッグ用カプセル描画
	DrawCapsule3D(headTopPos, toePos, capsuleWidth, capsuleDivNum, capsuleColor, capsuleColor, FALSE);
}
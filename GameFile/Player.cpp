#include"GameObject.h"
#include"ObjectTag.h"
#include"PadInput.h"
#include"Collision.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

const VECTOR Player::scale = VGet(0.125f, 0.125f, 0.125f);
const unsigned int Player::debugColor = GetColor(255, 255, 0);
VECTOR Player::headPos = initializePos;
VECTOR Player::angle = initializePos;
const VECTOR Player::fixAngle= VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f);

//オブジェクトの初期化
Player::Player(int modelHandle, vector<int> animationHandle):
	input(nullptr),
	addMove(initializePos),
	isGround(false),
	gravity(static_cast<float>(initializeNum)),
	status(STATUS::STAND),
	animationIndex(initializeNum),
	totalAnimTime(static_cast<float>(initializeNum)),
	playAnimTime(static_cast<float>(initializeNum)),
	groundLinePos()
{
	tag = ObjectTag::PLAYER;
	//クラスのインスタンス取得
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	MV1SetScale(this->modelHandle, scale);
	pos = VGet(1000.0f, 400.0f, 0.0f);

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
	//UpdateGravity();
	MV1SetPosition(modelHandle, pos);
	UpdateAnimation();
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	//当たり判定用線分の座標計算
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		for (int j = initializeNum; j < lineNum; j++)
		{
			//線分の1点目の座標設定
			if (j == initializeNum)
			{
				addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			}
			//線分の2点目の座標設定
			else
			{
				addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				
			}
			addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, lineSpace);
			groundLinePos[i][j] = VAdd(pos, addMove);
			addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));

			addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, (i - lineNum) * (lineSpace * lineNum / lineDivNum));
			groundLinePos[i][j] = VAdd(groundLinePos[i][j], addMove);
			addMove = VGet(static_cast<int>(initializeNum), static_cast<int>(initializeNum), static_cast<int>(initializeNum));
		}
	}
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

//重力処理の更新
void Player::UpdateGravity()
{
	gravity += addGravity;
	if (gravity >= maxGravity)
	{
		gravity = maxGravity;
	}
	pos.y -= gravity;
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
void Player::OnCollisionEnter(GameObject* other,const ObjectTag tag)
{
	if (tag == ObjectTag::FIELD)
	{
		for (int i = initializeNum; i < lineDivNum; i++)
		{
			HitFieldJudge(pos, other->GetModelHandle(), groundLinePos[i][0], groundLinePos[i][1]);
		}
	}
	if (tag == ObjectTag::OBSTACLE)
	{

	}
}

//オブジェクトの描画
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	//当たり判定デバッグ用描画
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		DrawLine3D(groundLinePos[i][0], groundLinePos[i][1], debugColor);
	}
}
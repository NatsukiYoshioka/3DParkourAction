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
	moveDirection(initializePos),
	moveDirectionX(initializePos),
	moveDirectionZ(initializePos),
	isHitWall(initializeNum),
	isLeft(false),
	isGround(false),
	isJump(false),
	isMove(false),
	isWallRun(false),
	gravity(static_cast<float>(initializeNum)),
	jump(static_cast<float>(initializeNum)),
	status(STATUS::STAND),
	animationIndex(initializeNum),
	totalAnimTime(static_cast<float>(initializeNum)),
	playAnimTime(static_cast<float>(initializeNum)),
	groundLinePos(),
	wallCollisionLinePos()
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
	UpdateGravity();
	MV1SetPosition(modelHandle, pos);
	UpdateAnimation();
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	//当たり判定用線分の座標計算
	CalcCollisionLine();
}

void Player::UpdateInput()
{
	//視点移動入力処理
	if (!isWallRun)
	{
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
	}

	//移動入力処理
	if (isGround && !isWallRun)
	{
		isMove = false;
		status = STATUS::STAND;
		//左スティック左倒し
		if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
		{
			pos = VAdd(pos, CalcLeftMove(addMove));

			isMove = true;
			status = STATUS::RUN_LEFT;
		}
		//左スティック右倒し
		if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
		{
			pos = VAdd(pos, CalcRightMove(addMove));

			isMove = true;
			status = STATUS::RUN_RIGHT;
		}
		//左スティック上倒し
		if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
		{
			pos = VAdd(pos, CalcFrontMove(addMove));

			isMove = true;
			status = STATUS::RUN;
		}
		//左スティック下倒し
		if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
		{
			pos = VAdd(pos, CalcBehindMove(addMove));

			isMove = true;
			status = STATUS::RUN_BACK;
		}

		//アクション入力処理
		//ジャンプ:Aボタン入力
		if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
		{
			isJump = true;
			moveDirectionX = initializePos;
			moveDirectionZ = initializePos;
			//左スティック左倒し
			if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
			}
			//左スティック右倒し
			if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
			}
			//左スティック上倒し
			if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
			{
				moveDirectionZ = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionZ = VNorm(moveDirectionZ);
			}
			//左スティック下倒し
			if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
			{
				moveDirectionZ = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionZ = VNorm(moveDirectionZ);
			}
			moveDirection = VAdd(moveDirectionX, moveDirectionZ);
			moveDirection = VNorm(moveDirection);
			jump = jumpPower;
			gravity = static_cast<float>(initializeNum);

			isGround = false;
			status = STATUS::JUMP;
			playAnimTime = static_cast<float>(initializeNum);
		}
	}
	else if (isWallRun)
	{
		isMove = false;
		//左スティック上倒し
		if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
		{
			pos = VAdd(pos, CalcFrontMove(addMove));
		}
		if (isLeft)
		{
			//左スティック左倒し
			if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
			{
				pos = VAdd(pos, CalcLeftMove(addMove));
			}
		}
		else
		{
			//左スティック右倒し
			if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
			{
				pos = VAdd(pos, CalcRightMove(addMove));
			}
		}
		//ジャンプ:Aボタン入力
		if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
		{
			moveDirectionZ = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			moveDirectionZ = VNorm(moveDirectionZ);
			isMove = true;
			if (isLeft)
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
				pos = VAdd(pos, CalcRightMove(addMove));
			}
			else
			{
				moveDirectionX = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				moveDirectionX = VCross(moveDirectionX, VGet(0.0f, 1.0f, 0.0f));
				moveDirectionX = VNorm(moveDirectionX);
				pos = VAdd(pos, CalcLeftMove(addMove));
			}
			moveDirection = VAdd(moveDirectionX, moveDirectionZ);
			moveDirection = VNorm(moveDirection);
			jump = jumpPower;
			gravity = static_cast<float>(initializeNum);

			status = STATUS::JUMP;
			playAnimTime = static_cast<float>(initializeNum);
			isWallRun = false;
		}
	}
	else
	{
		//空中でのプレイヤーの挙動
		if (isMove)
		{
			pos = VAdd(pos, VScale(moveDirection, moveSpeed));
		}
		jump -= addGravity;
		if (jump <= static_cast<float>(initializeNum))
		{
			jump = static_cast<float>(initializeNum);
		}
		if (status != STATUS::JUMP)
		{
			status = STATUS::FALL;
		}
		pos.y += jump;
	}
}

VECTOR Player::CalcLeftMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VCross(vec, VGet(0.0f, 1.0f, 0.0f));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

VECTOR Player::CalcRightMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VCross(vec, VGet(0.0f, 1.0f, 0.0f));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

VECTOR Player::CalcFrontMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

VECTOR Player::CalcBehindMove(VECTOR vec)
{
	vec = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	vec = VNorm(vec);
	vec = VScale(vec, moveSpeed);
	return vec;
}

//重力処理の更新
void Player::UpdateGravity()
{
	if (jump <= static_cast<float>(initializeNum))
	{
		gravity += addGravity;
		isGround = false;
	}
	
	if (gravity >= maxGravity)
	{
		gravity = maxGravity;
	}
	if (isWallRun)gravity = static_cast<float>(initializeNum);
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
		switch (status)
		{
		case STATUS::JUMP:
			status = STATUS::FALL;
			break;
		default:
			playAnimTime = static_cast<float>(initializeNum);
			break;
		}
	}

	MV1SetAttachAnimTime(modelHandle, animationIndex, playAnimTime);
}

//当たり判定線分の計算
void Player::CalcCollisionLine()
{
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		for (int j = initializeNum; j < lineDivNum; j++)
		{
			//地面の当たり判定線分
			addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, static_cast<float>((i - lineNum) * (groundLineSpace * lineDivNum / lineNum)));
			groundLinePos[i][j] = VAdd(VGet(pos.x, pos.y + groundLineWidth - maxGravity, pos.z), addMove);

			addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, static_cast<float>((j - lineNum) * (groundLineSpace * lineDivNum / lineNum)));
			groundLinePos[i][j] = VAdd(groundLinePos[i][j], addMove);

			//壁の当たり判定用線分
			for (int l = initializeNum; l < lineNum; l++)
			{
				if(l == initializeNum)
				{
					addMove = VTransform(VGet(0.1f, 0.0f, 0.0f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				}
				else addMove = VTransform(VGet(-0.1f, 0.0f, 0.0f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, wallCollisionLineWidth);
				wallCollisionLinePos[l][i][j] = VAdd(VGet(pos.x, pos.y + fixWallCollisionLinePosY, pos.z), addMove);

				addMove = VTransform(VGet(0.1f, 0.0f, 0.0f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, static_cast<float>((i - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum)));
				wallCollisionLinePos[l][i][j] = VAdd(wallCollisionLinePos[l][i][j], addMove);

				wallCollisionLinePos[l][i][j].y += static_cast<float>((j - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum));
			}

			//側面の当たり判定用線分
			for (int l = initializeNum; l < lineNum; l++)
			{
				if (l == initializeNum)
				{
					addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				}
				else addMove = VTransform(VGet(0.0f, 0.0f, -0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VCross(addMove, VGet(0.0f, 0.1f, 0.0f));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, wallCollisionLineWidth);
				sideCollisionLinePos[l][i][j] = VAdd(VGet(pos.x, pos.y + fixWallCollisionLinePosY, pos.z), addMove);

				addMove = VTransform(VGet(0.0f, 0.0f, 0.1f), MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VNorm(addMove);
				addMove = VScale(addMove, static_cast<float>((i - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum)));
				sideCollisionLinePos[l][i][j] = VAdd(sideCollisionLinePos[l][i][j], addMove);

				sideCollisionLinePos[l][i][j].y += static_cast<float>((j - lineNum) * (wallCollisionLineSpace * lineNum / lineDivNum));
			}
		}
	}
}

//当たり判定
void Player::OnCollisionEnter(GameObject* other,const ObjectTag tag)
{
	if (tag == ObjectTag::FIELD)
	{
		for (int i = initializeNum; i < lineDivNum; i++)
		{
			for (int j = initializeNum; j < lineDivNum; j++)
			{
				if (HitGroundJudge(pos, other->GetModelHandle(), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y + groundLineWidth, groundLinePos[i][j].z), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y - groundLineWidth, groundLinePos[i][j].z)))
				{
					CalcCollisionLine();
					isGround = true;
					isJump = false;
				}
				if (isGround)
				{
					if (HitWallJudge(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]))
					{
						CalcCollisionLine();
					}
				}
				else
				{
					isHitWall = WallRunProcess(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]);
					if (isHitWall && isJump)
					{
						if (isHitWall == hitLeft)isLeft = true;
						else isLeft = false;
						isWallRun = true;
						CalcCollisionLine();
					}
				}
				if (HitWallJudge(pos, other->GetModelHandle(), wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j]))
				{
					CalcCollisionLine();
				}
			}
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
		for (int j = initializeNum; j < lineDivNum; j++)
		{
			DrawLine3D(VGet(groundLinePos[i][j].x, groundLinePos[i][j].y + groundLineWidth, groundLinePos[i][j].z), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y - groundLineWidth, groundLinePos[i][j].z), debugColor);
			DrawLine3D(wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j], debugColor);
			DrawLine3D(sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j], debugColor);
		}
	}
}
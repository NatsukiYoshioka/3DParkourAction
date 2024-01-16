#include"GameObject.h"
#include"ObjectTag.h"
#include"PadInput.h"
#include"Collision.h"
#include"common.h"
#include"DxLib.h"
#include "Player.h"

const VECTOR Player::initPos = VGet(1025.0f, 420.0f, -200.0f);
const VECTOR Player::scale = VGet(0.125f, 0.125f, 0.125f);
const VECTOR Player::downLightDirection = VGet(0.0f, -1.0f, 0.0f);
const unsigned int Player::debugColor = GetColor(255, 255, 0);
VECTOR Player::headPos = initializePos;
VECTOR Player::angle = initializePos;
const VECTOR Player::fixAngle= VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f);
const VECTOR Player::crossCollisionLine = VGet(0.0f, 0.1f, 0.0f);
const VECTOR Player::transformWallCollisionLine = VGet(0.1f, 0.0f, 0.0f);
const VECTOR Player::transformReverseWallCollisionLine = VGet(-0.1f, 0.0f, 0.0f);

//オブジェクトの初期化
Player::Player(int modelHandle, vector<int> animationHandle):
	debug(false),
	isStart(false),
	input(nullptr),
	addMove(initializePos),
	lightDirection(initializePos),
	moveDirection(initializePos),
	moveDirectionX(initializePos),
	moveDirectionZ(initializePos),
	isHitWall(initializeNum),
	moveSpeed(initializeSpeed),
	isLeft(false),
	isGround(false),
	isJump(false),
	isMove(false),
	isWallRun(false),
	isWallJump(false),
	isSlide(false),
	isStandByToJumpOver(false),
	isStandByToBigJump(false),
	gravity(static_cast<float>(initializeNum)),
	jump(static_cast<float>(initializeNum)),
	status(STATUS::CROUCH),
	jumpAngle(initializePos),
	fixJumpOverPos(initializePos),
	fixSlidePos(initializePos),
	animationIndex(initializeNum),
	totalAnimTime(static_cast<float>(initializeNum)),
	playAnimTime(static_cast<float>(initializeNum)),
	spinePos(initializePos),
	groundLinePos(),
	wallCollisionLinePos(),
	sideCollisionLinePos()
{
	tag = ObjectTag::PLAYER;
	//クラスのインスタンス取得
	input = PadInput::GetInstance();

	this->modelHandle = MV1DuplicateModel(modelHandle);
	MV1SetScale(this->modelHandle, scale);
	pos = initPos;
	restartPos = pos;

	MV1SetRotationXYZ(this->modelHandle, fixAngle);

	this->animationHandle = animationHandle;

	//プレイヤーの初期状態を立ち状態にする
	animationIndex = MV1AttachAnim(this->modelHandle, initializeNum, this->animationHandle.at(static_cast<int>(status)));

	forwardLightHandle = CreateDirLightHandle(angle);
	downLightHandle = CreateDirLightHandle(downLightDirection);
}

//データの解放
Player::~Player()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
	DeleteLightHandleAll();
}

//オブジェクトの更新
void Player::Update(GameManager::SCENE nowScene)
{
	//DebugInput();
	if (!debug)
	{
		//ゲーム開始時の挙動
		if (nowScene == GameManager::SCENE::GAME && !isStart)
		{
			if (status != STATUS::CROUCHED_TO_STAND)playAnimTime = static_cast<float>(initializeNum);
			status = STATUS::CROUCHED_TO_STAND;
		}
		if (isStart)UpdateInput();
		if (!isWallRun)
		{
			MV1SetRotationXYZ(modelHandle, VGet(angle.x, angle.y + fixAngle.y, angle.z));
		}
		UpdateGravity();
		UpdateAnimation();
		//当たり判定用線分の座標計算
		CalcCollisionLine();
	}
	MV1SetPosition(modelHandle, pos);
	headPos = MV1GetFramePosition(modelHandle, headFrameIndex);
	UpdateLight();
	//落ちたらリスポーン
	if (pos.y <= restartHeight)
	{
		Respone();
	}
}

void Player::UpdateInput()
{
	if (!isSlide && status != STATUS::JUMP_OVER)
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
	}

	//移動入力処理
	if (isGround && !isWallRun && status != STATUS::SLIDE && status != STATUS::JUMP_OVER)
	{
		isMove = false;

		gravity = static_cast<float>(initializeNum);
		moveDirection = initializePos;
		moveDirectionX = initializePos;
		moveDirectionZ = initializePos;

		if (status != STATUS::CROUCH)status = STATUS::STAND;
		
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
		if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
		{
			pos = VAdd(pos, CalcFrontMove(addMove));

			isMove = true;
			status = STATUS::RUN;
		}
		//左スティック下倒し
		if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
		{
			pos = VAdd(pos, CalcBehindMove(addMove));

			isMove = true;
			status = STATUS::RUN_BACK;
		}

		//アクション入力処理
		//ジャンプ:Aボタン入力
		if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
		{
			if (!isStandByToJumpOver)
			{
				isJump = true;
				moveDirectionX = initializePos;
				moveDirectionZ = initializePos;
				jumpAngle = angle;
				//左スティック左倒し
				if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
				{
					moveDirectionX = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
					moveDirectionX = VCross(moveDirectionX, crossVector);
					moveDirectionX = VNorm(moveDirectionX);
				}
				//左スティック右倒し
				if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
				{
					moveDirectionX = VTransform(transformReverseVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
					moveDirectionX = VCross(moveDirectionX, crossVector);
					moveDirectionX = VNorm(moveDirectionX);
				}
				//左スティック上倒し
				if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
				{
					moveDirectionZ = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
					moveDirectionZ = VNorm(moveDirectionZ);
				}
				//左スティック下倒し
				if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
				{
					moveDirectionZ = VTransform(transformReverseVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
					moveDirectionZ = VNorm(moveDirectionZ);
				}

				jump = jumpPower;
				gravity = static_cast<float>(initializeNum);

				isGround = false;
				status = STATUS::JUMP;
				playAnimTime = static_cast<float>(initializeNum);
			}
			//障害物飛び越え処理
			else
			{
				status = STATUS::JUMP_OVER;
				playAnimTime = static_cast<float>(initializeNum);
				pos.y += fixPosYToJumpOver;
			}
		}
		isStandByToJumpOver = false;
		//スライディング:Bボタン入力
		if ((input->GetInput().Buttons[slideButtonIndex] || CheckHitKey(KEY_INPUT_C) != initializeNum) && status == STATUS::RUN)
		{
			playAnimTime = static_cast<float>(initializeNum);
			status = STATUS::SLIDE;
			isSlide = true;
		}
		moveDirection = VAdd(moveDirectionX, moveDirectionZ);
		moveDirection = VNorm(moveDirection);
	}
	//飛び越え中の処理
	else if (status == STATUS::JUMP_OVER)
	{
		moveDirection = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		moveDirection = VNorm(moveDirection);
		fixJumpOverPos = VAdd(fixJumpOverPos, VScale(moveDirection, slideSpeed));
		//大ジャンプ処理
		if (isStandByToBigJump)
		{
			//ジャンプ:Aボタン入力
			if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
			{
				status = STATUS::JUMP;
				playAnimTime = static_cast<float>(initializeNum);

				isStandByToJumpOver = false;
				isStandByToBigJump = false;
				isJump = true;
				isGround = false;

				jump = bigJumpPower;
				jumpAngle = angle;
				gravity = static_cast<float>(initializeNum);

				fixJumpOverPos = initializePos;
			}
		}
	}
	//スライディング中の処理
	else if (status == STATUS::SLIDE)
	{
		isGround = true;
		moveDirection = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
		moveDirection = VNorm(moveDirection);
		fixSlidePos = VAdd(fixSlidePos, VScale(moveDirection, slideSpeed));
		pos = VAdd(pos, VScale(moveDirection, slideSpeed));

		//ジャンプ:Aボタン入力
		if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
		{
			isSlide = false;
			isHitWall = false;

			isJump = true;
			jump = jumpPower;
			jumpAngle = angle;
			gravity = static_cast<float>(initializeNum);

			isGround = false;
			status = STATUS::JUMP;
			playAnimTime = static_cast<float>(initializeNum);

			pos = VAdd(pos, fixSlidePos);
			fixSlidePos = initializePos;
		}
	}
	//ウォールラン中の処理
	else if (isWallRun)
	{
		isMove = false;
		//左スティック上倒し
		pos = VAdd(pos, CalcFrontMove(addMove));
		//ジャンプ:Aボタン入力
		if (input->GetInput().Buttons[jumpButtonIndex] || CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
		{
			isMove = true;
			moveDirection = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			moveDirection = VNorm(moveDirection);
			
			jump = jumpPower;

			status = STATUS::JUMP;
			playAnimTime = static_cast<float>(initializeNum);
			isWallJump = true;
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
	isStandByToBigJump = false;
	isStandByToJumpOver = false;
}

//デバッグ用移動処理
void Player::DebugInput()
{
	debug = true;
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

	//左スティック左倒し
	if (input->GetInput().ThumbLX < initializeNum || CheckHitKey(KEY_INPUT_A) != initializeNum)
	{
		pos = VAdd(pos, VAdd(CalcLeftMove(addMove),CalcLeftMove(addMove)));
	}
	//左スティック右倒し
	if (input->GetInput().ThumbLX > initializeNum || CheckHitKey(KEY_INPUT_D) != initializeNum)
	{
		pos = VAdd(pos, VAdd(CalcRightMove(addMove), CalcRightMove(addMove)));
	}
	//左スティック上倒し
	if (input->GetInput().ThumbLY > initializeNum || CheckHitKey(KEY_INPUT_W) != initializeNum)
	{
		pos = VAdd(pos, VAdd(CalcFrontMove(addMove), CalcFrontMove(addMove)));
	}
	//左スティック下倒し
	if (input->GetInput().ThumbLY < initializeNum || CheckHitKey(KEY_INPUT_S) != initializeNum)
	{
		pos = VAdd(pos, VAdd(CalcBehindMove(addMove), CalcBehindMove(addMove)));
	}

	if (CheckHitKey(KEY_INPUT_SPACE) != initializeNum)
	{
		pos.y += moveSpeed * debugSpeed;
	}
	if (CheckHitKey(KEY_INPUT_LCONTROL) != initializeNum)
	{
		pos.y -= moveSpeed * debugSpeed;
	}
}

//左移動処理
VECTOR Player::CalcLeftMove(VECTOR vec)
{
	if(!isWallRun)vec = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	else vec = VTransform(transformVector, MMult(MMult(MGetRotZ(jumpAngle.z), MGetRotX(jumpAngle.x)), MGetRotY(jumpAngle.y)));
	vec = VCross(vec, crossVector);
	vec = VNorm(vec);
	moveDirectionX = vec;
	vec = VScale(vec, moveSpeed);
	return vec;
}

//右移動処理
VECTOR Player::CalcRightMove(VECTOR vec)
{
	if (!isWallRun)vec = VTransform(transformReverseVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	else vec = VTransform(transformReverseVector, MMult(MMult(MGetRotZ(jumpAngle.z), MGetRotX(jumpAngle.x)), MGetRotY(jumpAngle.y)));
	vec = VCross(vec, crossVector);
	vec = VNorm(vec);
	moveDirectionX = vec;
	vec = VScale(vec, moveSpeed);
	return vec;
}

//前移動処理
VECTOR Player::CalcFrontMove(VECTOR vec)
{
	if (!isWallRun)vec = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	else vec = VTransform(transformVector, MMult(MMult(MGetRotZ(jumpAngle.z), MGetRotX(jumpAngle.x)), MGetRotY(jumpAngle.y)));
	vec = VNorm(vec);
	moveDirectionZ = vec;
	vec = VScale(vec, moveSpeed);
	return vec;
}

//後方移動処理
VECTOR Player::CalcBehindMove(VECTOR vec)
{
	if (!isWallRun)vec = VTransform(transformReverseVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	else vec = VTransform(transformReverseVector, MMult(MMult(MGetRotZ(jumpAngle.z), MGetRotX(jumpAngle.x)), MGetRotY(jumpAngle.y)));
	vec = VNorm(vec);
	moveDirectionZ = vec;
	vec = VScale(vec, moveSpeed);
	return vec;
}

//重力処理の更新
void Player::UpdateGravity()
{
	if (jump <= static_cast<float>(initializeNum) && status != STATUS::JUMP_OVER)
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
	//アニメーション遷移の特殊処理
	if (playAnimTime >= totalAnimTime)
	{
		switch (status)
		{
		case STATUS::CROUCHED_TO_STAND:
			isStart = true;
			status = STATUS::STAND;
			break;
		case STATUS::JUMP:
			status = STATUS::FALL;
			break;
		case STATUS::LEFT_WALLRUN:
			isWallRun = false;
			status = STATUS::FALL;
			break;
		case STATUS::RIGHT_WALLRUN:
			isWallRun = false;
			status = STATUS::FALL;
			break;
		case STATUS::SLIDE:
			status = STATUS::CROUCH;
			pos = VAdd(pos, fixSlidePos);
			fixSlidePos = initializePos;
			isSlide = false;
			break;
		case STATUS::JUMP_OVER:
			status = STATUS::FALL;
			pos = VAdd(pos, fixJumpOverPos);
			fixJumpOverPos = initializePos;
			isStandByToJumpOver = false;
			isGround = false;
			break;
		default:
			playAnimTime = static_cast<float>(initializeNum);
			break;
		}
	}
	if (status == STATUS::JUMP_OVER && playAnimTime >= totalAnimTime / bipartition)
	{
		isStandByToBigJump = true;
	}

	MV1SetAttachAnimTime(modelHandle, animationIndex, playAnimTime);
}

//ライトの更新
void Player::UpdateLight()
{
	SetLightPositionHandle(forwardLightHandle, pos);
	lightDirection = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	SetLightDirectionHandle(forwardLightHandle, lightDirection);
	SetLightPositionHandle(downLightHandle, VGet(pos.x, pos.y + downLightHeight, pos.z));
}

//リスポーン処理
void Player::Respone()
{
	pos = restartPos;
	moveDirection = initializePos;
	moveDirectionX = initializePos;
	moveDirectionZ = initializePos;
}

//当たり判定線分の計算
void Player::CalcCollisionLine()
{
	spinePos = MV1GetFramePosition(modelHandle, spineFrameIndex);
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		for (int j = initializeNum; j < lineDivNum; j++)
		{
			//地面の当たり判定線分
			addMove = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VCross(addMove, crossCollisionLine);
			addMove = VNorm(addMove);
			addMove = VScale(addMove, static_cast<float>((i - lineNum) * (groundLineSpace * lineDivNum / lineNum)));
			groundLinePos[i][j] = VAdd(VGet(pos.x, pos.y + groundLineWidth - maxGravity, pos.z), addMove);

			addMove = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
			addMove = VNorm(addMove);
			addMove = VScale(addMove, static_cast<float>((j - lineNum) * (groundLineSpace * lineDivNum / lineNum)));
			groundLinePos[i][j] = VAdd(groundLinePos[i][j], addMove);

			//壁の当たり判定用線分
			for (int l = initializeNum; l < lineNum; l++)
			{
				if (l == initializeNum)
				{
					addMove = VTransform(transformWallCollisionLine, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				}
				else addMove = VTransform(transformReverseWallCollisionLine, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VCross(addMove, crossCollisionLine);
				addMove = VNorm(addMove);
				addMove = VScale(addMove, wallCollisionLineWidth);
				if (status != STATUS::SLIDE && !isWallRun)wallCollisionLinePos[l][i][j] = VAdd(VGet(pos.x, pos.y + fixWallCollisionLinePosY, pos.z), addMove);
				else
				{
					wallCollisionLinePos[l][i][j] = VAdd(VGet(spinePos.x, spinePos.y, spinePos.z), addMove);
				}

				addMove = VTransform(transformWallCollisionLine, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
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
					addMove = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				}
				else addMove = VTransform(transformReverseVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
				addMove = VCross(addMove, crossCollisionLine);
				addMove = VNorm(addMove);
				addMove = VScale(addMove, wallCollisionLineWidth);
				if (status != STATUS::SLIDE && !isWallRun)sideCollisionLinePos[l][i][j] = VAdd(VGet(pos.x, pos.y + fixWallCollisionLinePosY, pos.z), addMove);
				else
				{
					sideCollisionLinePos[l][i][j] = VAdd(VGet(spinePos.x, spinePos.y, spinePos.z), addMove);
				}

				addMove = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
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
	for (int i = initializeNum; i < lineDivNum; i++)
	{
		for (int j = initializeNum; j < lineDivNum; j++)
		{
			//フィールドとの当たり判定
			if (tag == ObjectTag::FIELD)
			{
				//地面との当たり判定
				if (HitGroundJudge(pos, other->GetModelHandle(), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y + groundLineWidth, groundLinePos[i][j].z), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y - groundLineWidth, groundLinePos[i][j].z)))
				{
					CalcCollisionLine();
					isGround = true;
					isWallRun = false;
					isWallJump = false;
					isJump = false;
					jump = static_cast<float>(initializeNum);
					restartPos = pos;
				}
				//地面にいるときの壁との当たり判定
				if (isGround)
				{
					if (HitWallJudge(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]))
					{
						CalcCollisionLine();
					}
				}
				//空中で壁に当たった時の当たり判定
				else
				{
					isHitWall = WallRunProcess(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]);
					if (isHitWall && isJump && !isWallJump)
					{
						if (isHitWall == hitLeft)
						{
							isLeft = true;
							status = STATUS::LEFT_WALLRUN;
						}
						else
						{
							isLeft = false;
							status = STATUS::RIGHT_WALLRUN;
						}
						if (!isWallRun)playAnimTime = static_cast<float>(initializeNum);
						isWallRun = true;
						CalcCollisionLine();
					}
					else if (HitWallJudge(pos, other->GetModelHandle(), wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j]))
					{
						CalcCollisionLine();
					}
				}
			}
			if (tag == ObjectTag::SLIDE_OBSTACLE || tag == ObjectTag::OBSTACLE)
			{
				//飛び越えできる位置に障害物があるかどうか判定
				if (jumpOverDistance * jumpOverDistance >= (wallCollisionLinePos[initializeNum][i][j].x - other->GetPos().x) * (wallCollisionLinePos[initializeNum][i][j].x - other->GetPos().x) + (wallCollisionLinePos[initializeNum][i][j].y - other->GetPos().y) * (wallCollisionLinePos[initializeNum][i][j].y - other->GetPos().y) + (wallCollisionLinePos[initializeNum][i][j].z - other->GetPos().z) * (wallCollisionLinePos[initializeNum][i][j].z - other->GetPos().z))
					isStandByToJumpOver = true;
				else if (!isStandByToJumpOver) isStandByToJumpOver = false;
			}
			//障害物との当たり判定
			if (tag == ObjectTag::SLIDE_OBSTACLE)
			{
				if (HitWallJudge(pos, other->GetModelHandle(), wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j]))
				{
					if (status != STATUS::SLIDE)
					{
						CalcCollisionLine();
						isStandByToJumpOver = false;
					}
				}
				if (HitWallJudge(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]))
				{
					if (status != STATUS::SLIDE)
					{
						CalcCollisionLine();
						isStandByToJumpOver = false;
					}
				}
			}
			if (tag == ObjectTag::OBSTACLE)
			{
				if (HitWallJudge(pos, other->GetModelHandle(), wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j]))
				{
					CalcCollisionLine();
				}
				if (HitWallJudge(pos, other->GetModelHandle(), sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j]))
				{
					CalcCollisionLine();
				}
			}
		}
	}
}

//オブジェクトの描画
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	//当たり判定デバッグ用描画
	/*for (int i = initializeNum; i < lineDivNum; i++)
	{
		for (int j = initializeNum; j < lineDivNum; j++)
		{
			DrawLine3D(VGet(groundLinePos[i][j].x, groundLinePos[i][j].y + groundLineWidth, groundLinePos[i][j].z), VGet(groundLinePos[i][j].x, groundLinePos[i][j].y - groundLineWidth, groundLinePos[i][j].z), debugColor);
			DrawLine3D(wallCollisionLinePos[initializeNum][i][j], wallCollisionLinePos[1][i][j], debugColor);
			DrawLine3D(sideCollisionLinePos[initializeNum][i][j], sideCollisionLinePos[1][i][j], debugColor);
		}
	}*/
}
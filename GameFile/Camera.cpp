#include"GameObject.h"
#include"ObjectTag.h"
#include"Player.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Camera.h"

//コンストラクタ
Camera::Camera():
	forwardPos(firstForwardPos),
	rotateV(static_cast<float>(initializeNum)),
	fov(initializeFov),
	angle(initializePos),
	addPos(initializePos)
{
	tag = ObjectTag::CAMERA;
	input = PadInput::GetInstance();
	SetCameraNearFar(cameraNear, cameraFar);
	SetupCamera_Perspective(fov);
}

//データ解放
Camera::~Camera()
{

}

//オブジェクトの初期化
void Camera::Initialize()
{
	forwardPos=firstForwardPos;
	rotateV=static_cast<float>(initializeNum);
	angle=initializePos;
	addPos=initializePos;
}

//カメラの更新
void Camera::Update()
{
	if(GameManager::GetGameStatus() == GameManager::SCENE::TITLE)Initialize();
	if (GameManager::GetGameStatus() == GameManager::SCENE::GAME)UpdateInput();

	//カメラのY座標を設定
	pos = Player::GetHeadPos();
	pos.y += fixPosY;

	//カメラの向きを更新
	angle = Player::GetAngle();
	angle.x += rotateV;

	if (GameManager::GetGameStatus() == GameManager::SCENE::GAME)
	{
		forwardPos += (fixForwardPos - firstForwardPos) / sceneTransitionTime;
		if (forwardPos >= fixForwardPos)forwardPos = fixForwardPos;
	}

	//カメラを前に押し出し
	addPos = VTransform(transformVector, MMult(MMult(MGetRotZ(angle.z), MGetRotX(angle.x)), MGetRotY(angle.y)));
	addPos = VNorm(addPos);
	addPos = VScale(addPos, forwardPos);
	pos = VAdd(pos, addPos);

	//カメラの位置と向きをセット
	SetCameraPositionAndAngle(pos, angle.x, angle.y, angle.z);
}

//入力処理更新
void Camera::UpdateInput()
{
	//縦方向カメラ移動入力処理
	//右スティック上倒し
	if (input->GetInput().ThumbRY > initializeNum || CheckHitKey(KEY_INPUT_UP) != initializeNum)
	{
		rotateV -= directionSpeed;
		if (rotateV <= maxUpDirection)
		{
			rotateV = maxUpDirection;
		}
	}
	//右スティック下倒し
	if (input->GetInput().ThumbRY < initializeNum || CheckHitKey(KEY_INPUT_DOWN) != initializeNum)
	{
		rotateV += directionSpeed;
		if (rotateV >= maxDownDirection)
		{
			rotateV = maxDownDirection;
		}
	}
}
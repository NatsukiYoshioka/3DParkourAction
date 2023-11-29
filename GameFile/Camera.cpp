#include"GameObject.h"
#include"Player.h"
#include"PadInput.h"
#include"common.h"
#include"DxLib.h"
#include "Camera.h"

//コンストラクタ
Camera::Camera():
	rotateV(static_cast<float>(initializeNum))
{
	input = PadInput::GetInstance();
}

//データ解放
Camera::~Camera()
{

}

//カメラの更新
void Camera::Update()
{
	UpdateInput();
	SetCameraPositionAndAngle(Player::GetHeadPos(), Player::GetAngle().x + rotateV, Player::GetAngle().y, Player::GetAngle().z);
}

//入力処理更新
void Camera::UpdateInput()
{
	//縦方向カメラ移動入力処理
	//右スティック上倒し
	if (input->GetInput().ThumbRY > initializeNum || CheckHitKey(KEY_INPUT_UP) != initializeNum)
	{
		rotateV -= directionSpeed;
	}
	//右スティック下倒し
	if (input->GetInput().ThumbRY < initializeNum || CheckHitKey(KEY_INPUT_DOWN) != initializeNum)
	{
		rotateV += directionSpeed;
	}
}
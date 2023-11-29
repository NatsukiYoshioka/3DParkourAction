#include"GameObject.h"
#include"Player.h"
#include"DxLib.h"
#include "Camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::Update()
{
	pos = Player::GetHeadPos();
	
}
#include"GameObject.h"
#include "Player.h"

Player::Player(int modelHandle)
{
	this->modelHandle = MV1DuplicateModel(modelHandle);
}

Player::~Player()
{
	if (modelHandle != -1)
	{
		MV1DeleteModel(modelHandle);
	}
}

void Player::Update()
{

}

void Player::Draw()
{

}
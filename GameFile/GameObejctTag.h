#pragma once

/// <summary>
/// �I�u�W�F�N�g�̃^�O
/// </summary>
enum class ObjectTag :unsigned char
{
	PLAYER,
	FIELD,
	OBSTACLE,
	CAMERA
};

//�A�N�e�B�u�ȃ^�O�̌����p
static constexpr ObjectTag objectAllTag[] =
{
	ObjectTag::PLAYER,
	ObjectTag::FIELD,
	ObjectTag::OBSTACLE,
	ObjectTag::CAMERA
};
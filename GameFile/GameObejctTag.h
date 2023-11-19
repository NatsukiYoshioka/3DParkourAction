#pragma once

/// <summary>
/// オブジェクトのタグ
/// </summary>
enum class ObjectTag :unsigned char
{
	PLAYER,
	FIELD,
	OBSTACLE,
	CAMERA
};

//アクティブなタグの検索用
static constexpr ObjectTag objectAllTag[] =
{
	ObjectTag::PLAYER,
	ObjectTag::FIELD,
	ObjectTag::OBSTACLE,
	ObjectTag::CAMERA
};
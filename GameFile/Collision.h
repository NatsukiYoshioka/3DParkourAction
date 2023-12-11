#pragma once
#include<DxLib.h>

static constexpr int frameIndex = -1;       //フレームの番号

/// <summary>
/// 地面との当たり判定
/// </summary>
///  <param name="pos">フィールドと比較するオブジェクトの座標</param>
///  <param name="modelHandle">フィールドのモデルハンドル</param>
///  <param name="linePos1">当たり判定用線分の1点目の座標</param>
///  <param name="linePos2">当たり判定用線分の2点目の座標</param>
///  <returns>当たったかどうか</returns>
bool HitGroundJudge(VECTOR &pos,int modelHandle,VECTOR linePos1,VECTOR linePos2);

/// <summary>
/// 壁との当たり判定
/// </summary>
///  <param name="pos">フィールドと比較するオブジェクトの座標</param>
///  <param name="modelHandle">フィールドのモデルハンドル</param>
///  <param name="linePos1">当たり判定用線分の1点目の座標</param>
///  <param name="linePos2">当たり判定用線分の2点目の座標</param>
///  <returns>当たったかどうか</returns>
bool HitWallJudge(VECTOR& pos, int modelHandle, VECTOR linePos1, VECTOR linePos2);
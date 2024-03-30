#pragma once
#include<DxLib.h>

static constexpr int frameIndex = -1;       //フレームの番号
static constexpr int hitLeft = 1;			//左の壁に当たった時の戻り値
static constexpr int hitRight = 2;			//右の壁に当たった時の戻り値

/// <summary>
/// 地面との当たり判定
/// </summary>
///  <param name="pos">フィールドと比較するオブジェクトの座標</param>
///  <param name="modelHandle">フィールドのモデルハンドル</param>
///  <param name="linePos1">当たり判定用線分の1点目の座標</param>
///  <param name="linePos2">当たり判定用線分の2点目の座標</param>
///  <returns>当たったかどうか</returns>
bool JudgeHitGround(VECTOR &pos,int modelHandle,VECTOR linePos1,VECTOR linePos2);

/// <summary>
/// 壁との当たり判定
/// </summary>
///  <param name="pos">フィールドと比較するオブジェクトの座標</param>
///  <param name="modelHandle">フィールドのモデルハンドル</param>
///  <param name="linePos1">当たり判定用線分の1点目の座標</param>
///  <param name="linePos2">当たり判定用線分の2点目の座標</param>
///  <returns>当たったかどうか</returns>
bool JudgeHitWall(VECTOR& pos, int modelHandle, VECTOR linePos1, VECTOR linePos2);

/// <summary>
/// ウォールラン当たり判定処理
/// </summary>
///  <param name="pos">フィールドと比較するオブジェクトの座標</param>
///  <param name="modelHandle">フィールドのモデルハンドル</param>
///  <param name="linePos1">当たり判定用線分の1点目の座標</param>
///  <param name="linePos2">当たり判定用線分の2点目の座標</param>
///  <returns>当たったかどうか、左右どちらの壁に当たったか</returns>
int WallRunProcess(VECTOR& pos, int modelHandle, VECTOR linePos1, VECTOR linePos2);
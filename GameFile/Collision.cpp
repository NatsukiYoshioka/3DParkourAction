#include"common.h"
#include"DxLib.h"
#include"Collision.h"

//地面との当たり判定
bool HitGroundJudge(VECTOR &pos, int modelHandle, VECTOR linePos1, VECTOR linePos2)
{
    MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(modelHandle, frameIndex, linePos1, linePos2);
    if (hitPoly.HitFlag)
    {
        pos.y += hitPoly.HitPosition.y - linePos2.y;
        return true;
    }
    return false;
}

//壁との当たり判定
bool HitWallJudge(VECTOR& pos, int modelHandle, VECTOR linePos1, VECTOR linePos2)
{
    MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(modelHandle, frameIndex, linePos1, linePos2);
    if (hitPoly.HitFlag)
    {
        if (VSize(VSub(hitPoly.HitPosition, linePos1)) < VSize(VSub(hitPoly.HitPosition, linePos2)))
        {
            pos = VAdd(pos, VSub(hitPoly.HitPosition, linePos1));
        }
        else
        {
            pos = VAdd(pos, VSub(hitPoly.HitPosition, linePos2));
        }
        return true;
    }
    return false;
}

//ウォールラン当たり判定処理
int WallRunProcess(VECTOR& pos, int modelHandle, VECTOR linePos1, VECTOR linePos2)
{
    MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(modelHandle, frameIndex, linePos1, linePos2);
    if (hitPoly.HitFlag)
    {
        if (VSize(VSub(hitPoly.HitPosition, linePos1)) < VSize(VSub(hitPoly.HitPosition, linePos2)))
        {
            pos = VAdd(pos, VSub(hitPoly.HitPosition, linePos1));
            return hitLeft;
        }
        else
        {
            pos = VAdd(pos, VSub(hitPoly.HitPosition, linePos2));
            return hitRight;
        }
    }
    return initializeNum;
}
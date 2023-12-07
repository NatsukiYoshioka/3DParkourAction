#include"DxLib.h"
#include"Collision.h"

//フィールドとの当たり判定
bool HitFieldJudge(VECTOR &pos, int modelHandle, VECTOR linePos1, VECTOR linePos2)
{
    MV1_COLL_RESULT_POLY hitPoly = MV1CollCheck_Line(modelHandle, frameIndex, linePos1, linePos2);
    if (hitPoly.HitFlag)
    {
        pos.y += hitPoly.HitPosition.y - linePos2.y;
        return true;
    }
    return false;
}
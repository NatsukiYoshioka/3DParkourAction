#include"DxLib.h"
#include"Collision.h"

//’n–Ê‚Æ‚Ì“–‚½‚è”»’è
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

//•Ç‚Æ‚Ì“–‚½‚è”»’è
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
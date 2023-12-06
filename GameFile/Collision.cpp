#include"DxLib.h"
#include"Collision.h"

void HitFieldJudge(VECTOR &pos, int modelHandle, VECTOR linePos1, VECTOR linePos2)
{
    MV1_COLL_RESULT_POLY_DIM hitPoly = MV1CollCheck_LineDim(modelHandle, frameIndex, linePos1, linePos2);
}
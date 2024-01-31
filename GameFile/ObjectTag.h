#pragma once

/// <summary>
/// オブジェクトのタグ
/// </summary>
enum class ObjectTag :unsigned char
{
    PLAYER,         //プレイヤータグ
    CAMERA,         //カメラタグ
    FIELD,          //フィールドタグ
    OBSTACLE,       //障害物タグ
    SLIDE_OBSTACLE, //くぐれる障害物タグ
    PORTAL,         //ポータルタグ
    GROUND,         //地面タグ
    SKYDOME,        //スカイドームタグ
    UI              //UIタグ
};
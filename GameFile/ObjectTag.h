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
    OTHER_OBSTACLE, //その他オブジェクト
    SKYDOME,        //スカイドームタグ
    UI              //UIタグ
};
#pragma once
#include<DxLib.h>

class GameOnject;

class Camera:public GameObject
{
public:
	/// <summary>
	/// 
	/// </summary>
	Camera();

	/// <summary>
	/// �f�[�^�̉��
	/// </summary>
	~Camera();

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V
	/// </summary>
	void Update();

	void Draw(){}

	/// <summary>
	/// �I�u�W�F�N�g�̍��W�̎擾
	/// </summary>
	/// <returns></returns>
	VECTOR GetPos() { return pos; }
};


#pragma once
#include<DxLib.h>

class GameOnject;

/// <summary>
/// �J�����̐���N���X
/// </summary>
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
};


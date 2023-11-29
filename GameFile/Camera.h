#pragma once
#include<DxLib.h>

class GameOnject;
class PadInput;

/// <summary>
/// �J�����̐���N���X
/// </summary>
class Camera:public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
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

	/// <summary>
	/// ���͏����X�V
	/// </summary>
	void UpdateInput();

	void Draw(){}

private:
	PadInput* input;		//�R���g���[���[���͏��Ǘ��N���X
	float rotateV;			//�J����X����]��

	static constexpr float directionSpeed = 0.05f;		//�����]�����x
};


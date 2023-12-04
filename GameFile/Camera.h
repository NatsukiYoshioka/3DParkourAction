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
	VECTOR angle;			//�J�����̌���
	VECTOR addPos;			//�J�����̈ʒu���Z��

	float rotateV;			//�J����X����]��

	static constexpr float fixPosY = 12.5f;				//�J����Y���W������
	static constexpr float fixFoewardPos = 12.5f;		//�J�����O�����o����

	static constexpr float directionSpeed = 0.05f;						//�����]�����x
	static constexpr float maxUpDirection = -90.0f * DX_PI_F / 180.0f;	//�J�����̏�������x
	static constexpr float maxDownDirection = 60.0f * DX_PI_F / 180.0f;	//�J�����̉��������x

	static constexpr float cameraNear = 2.5f;			//�J�����̎�O�`��͈�
	static constexpr float cameraFar = 20000.0f;		//�J�����̉��`�拗��
};


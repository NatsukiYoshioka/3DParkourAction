#pragma once
#include"ObjectTag.h"
#include"common.h"
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
	void Update(GameManager::SCENE nowScene);

	/// <summary>
	/// ���͏����X�V
	/// </summary>
	void UpdateInput();

	void Draw(){}

	/// <summary>
	/// ���f���n���h���擾
	/// </summary>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle() { return initializeNum; }

	/// <summary>
	/// �^�O�̎擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�^�O</returns>
	ObjectTag GetObjectTag() { return tag; }

	/// <summary>
	/// ���W�̎擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̍��W</returns>
	VECTOR GetPos() { return pos; }

private:
	PadInput* input;		//�R���g���[���[���͏��Ǘ��N���X
	VECTOR angle;			//�J�����̌���
	VECTOR addPos;			//�J�����̈ʒu���Z��

	float forwardPos;		//�J�����O�����o����
	float rotateV;			//�J����X����]��
	float fov;				//����p

	static constexpr float fixPosY = 5.0f;				//�J����Y���W������
	static constexpr float fixForwardPos = 7.5f;		//�J�����O�����o���ʌ��E�l
	static constexpr float firstForwardPos = -30.5f;	//�J�����̏��������o����
	//static constexpr float fixForwardPos = -120.5f;	//�A�j���[�V�����f�o�b�O�p

	static constexpr float directionSpeed = 0.025f;						//�����]�����x
	static constexpr float maxUpDirection = -90.0f * DX_PI_F / 180.0f;	//�J�����̏�������x
	static constexpr float maxDownDirection = 70.0f * DX_PI_F / 180.0f;	//�J�����̉��������x

	static constexpr float cameraNear = 0.5f;			//�J�����̎�O�`��͈�
	static constexpr float cameraFar = 8000.0f;		//�J�����̉��`�拗��

	static constexpr float initializeFov = 90.0f;
};


#pragma once
#include"common.h"
#include<vector>
#include<DxLib.h>

using namespace std;

class GameObject;
class PadInput;

class Player :public GameObject
{
public:
	/// <summary>
	/// �v���C���[�̏��
	/// </summary>
	enum class STATUS
	{
		CROUCHED_TO_STAND,			//�����オ��
		CROUCH,						//���Ⴊ��
		DEAD_FALL,					//����
		FALL,						//�~���
		FALLING_TO_ROLL,			//�O�]���n
		JUMP,						//�W�����v
		JUMP_OVER,					//��щz����
		LAND,						//���n
		LEFT_WALLRUN,				//���ǃE�H�[������
		RIGHT_WALLRUN,				//�E�ǃE�H�[������
		RUN,						//����
		SLIDE,						//�X���C�f�B���O
		STAND,						//����
		CROUNSHING_WALK,			//���Ⴊ�ݕ���
		STANDING_TO_CROUCH,			//�������炵�Ⴊ��
		RUN_BACK,					//��둖��
		RUN_RIGHT,					//�E����
		RUN_LEFT					//������
	};

	/// <summary>
	/// �I�u�W�F�N�g�̏�����
	/// </summary>
	/// <param name="modelHandle">���f���n���h��</param>
	/// <param name="animationHandle">�A�j���[�V�����n���h����vector�z��</param>
	Player(int modelHandle, vector<int> animationHandle);

	/// <summary>
	/// �f�[�^�̉��
	/// </summary>
	~Player();

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���͂ɂ�鋓���̍X�V
	/// </summary>
	void UpdateInput();

	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	void UpdateAnimation();

	/// <summary>
	/// ���̃I�u�W�F�N�g�Ƃ̓����蔻��
	/// </summary>
	/// <param name="other">���I�u�W�F�N�g</param>
	void OnCollisionEnter(const GameObject* other)override;

	/// <summary>
	/// �I�u�W�F�N�g�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I�u�W�F�N�g�̍��W�̎擾
	/// </summary>
	/// <returns></returns>
	static VECTOR GetHeadPos() { return headPos; }

	/// <summary>
	/// �v���C���[�̌������擾
	/// </summary>
	/// <returns>�v���C���[�̌���</returns>
	static VECTOR GetAngle() { return angle; }

	int GetModelHandle() { return initializeNum; }

private:
	vector<int> animationHandle;		//�A�j���[�V�����̔z��
	STATUS status;						//�v���C���[�̏��

	PadInput* input;					//�R���g���[���[���͊Ǘ��N���X�̃A�h���X

	static const VECTOR scale;			//���f���̃X�P�[��

	static constexpr float capsuleWidth = 5.0f;		//�����蔻��J�v�Z���̕�
	static constexpr int capsuleDivNum = 10;		//�����蔻��J�v�Z���̃|���S���ׂ̍���
	static const unsigned int capsuleColor;			//�����蔻��J�v�Z���̃J���[

	VECTOR addMove;									//�v���C���[�̈ړ����Z�l
	static constexpr float moveSpeed = 2.0f;		//�v���C���[�̈ړ����x�ړ����x

	static VECTOR angle;							//�v���C���[�̌���
	static constexpr float directionSpeed = 0.1f;	//�v���C���[�̕����]�����x

	static const VECTOR fixAngle;				//���f���̕����C��

	int animationIndex;								//�A�j���[�V�����ԍ�
	float totalAnimTime;							//�A�j���[�V�����̑��Đ�����
	float playAnimTime;								//�A�j���[�V�����̍Đ�����
	static constexpr float animationSpeed = 1.0f;	//�A�j���[�V�����Đ����x

	static VECTOR headPos;						//���̃t���[���̍��W
	static constexpr int headFrameIndex = 5;	//���̃t���[���̔ԍ�

	VECTOR headTopPos;							//���̒��_�̃t���[���̍��W
	static constexpr int headTopFrameIndex = 6;	//���̒��_�̃t���[���̔ԍ�

	VECTOR toePos;								//�ܐ�̃t���[���̍��W
	static constexpr int toeFrameIndex = 0;		//�ܐ�̃t���[���̔ԍ�
	static constexpr float fixToePosY = 2.5f;	//�ܐ��Y���W������
};


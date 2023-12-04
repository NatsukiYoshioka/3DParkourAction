#pragma once
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

private:
	vector<int> animationHandle;		//�A�j���[�V�����̔z��
	STATUS status;						//�v���C���[�̏��

	PadInput* input;					//�R���g���[���[���͊Ǘ��N���X�̃A�h���X

	static const VECTOR scale;

	VECTOR addMove;									//�v���C���[�̈ړ����Z�l
	static constexpr float moveSpeed = 4.0f;		//�v���C���[�̈ړ����x�ړ����x

	static VECTOR angle;							//�v���C���[�̌���
	static constexpr float directionSpeed = 0.1f;	//�v���C���[�̕����]�����x

	static const VECTOR fixAngle;				//���f���̕����C��

	float totalAnimTime;				//�A�j���[�V�����̑��Đ�����
	float playAnimTime;							//�A�j���[�V�����̍Đ�����

	static VECTOR headPos;						//���̃t���[���̍��W
	static constexpr int headFrameIndex = 5;	//���̃t���[���̔ԍ�
};


#pragma once
#include"ObjectTag.h"
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
	/// ���[���h���W���ړ��v�Z�֐�
	/// </summary>
	/// <param name="vec">���Z����x�N�g��</param>
	/// <returns>���Z����x�N�g��</returns>
	VECTOR CalcLeftMove(VECTOR vec);

	/// <summary>
	/// ���[���h���W�E�ړ��v�Z�֐�
	/// </summary>
	/// <param name="vec">���Z����x�N�g��</param>
	/// <returns>���Z����x�N�g��</returns>
	VECTOR CalcRightMove(VECTOR vec);

	/// <summary>
	/// ���[���h���W�O�ړ��v�Z�֐�
	/// </summary>
	/// <param name="vec">���Z����x�N�g��</param>
	/// <returns>���Z����x�N�g��</returns>
	VECTOR CalcFrontMove(VECTOR vec);

	/// <summary>
	/// ���[���h���W���ړ��v�Z�֐�
	/// </summary>
	/// <param name="vec">���Z����x�N�g��</param>
	/// <returns>���Z����x�N�g��</returns>
	VECTOR CalcBehindMove(VECTOR vec);

	/// <summary>
	/// �d�͏����̍X�V
	/// </summary>
	void UpdateGravity();

	/// <summary>
	/// �A�j���[�V�����̍X�V
	/// </summary>
	void UpdateAnimation();

	/// <summary>
	/// �����蔻������̌v�Z
	/// </summary>
	void CalcCollisionLine();

	/// <summary>
	/// ���̃I�u�W�F�N�g�Ƃ̓����蔻��
	/// </summary>
	/// <param name="other">���I�u�W�F�N�g</param>
	void OnCollisionEnter(GameObject* other,const ObjectTag tag)override;

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

	/// <summary>
	/// ���f���n���h���擾
	/// </summary>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle() { return initializeNum; }

	/// <summary>
	/// �I�u�W�F�N�g�^�O�擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�^�O</returns>
	ObjectTag GetObjectTag() { return tag; }

	/// <summary>
	/// ���W�擾
	/// </summary>
	/// <returns>�I�u�W�F�N�g�̍��W</returns>
	VECTOR GetPos() { return pos; }

private:
	vector<int> animationHandle;		//�A�j���[�V�����̔z��
	STATUS status;						//�v���C���[�̏��

	PadInput* input;					//�R���g���[���[���͊Ǘ��N���X�̃A�h���X

	static const VECTOR scale;			//���f���̃X�P�[��

	static const unsigned int debugColor;			//�����蔻��J�v�Z���̃J���[

	VECTOR addMove;									//�v���C���[�̈ړ����Z�l
	VECTOR moveDirection;							//�v���C���[�̌����ׂ�����
	VECTOR moveDirectionX;							//�v���C���[�̃��[�J��X���Ői�ނׂ�����
	VECTOR moveDirectionZ;							//�v���C���[�̃��[�J��Z���Ői�ނׂ�����
	int isHitWall;									//�ǂɓ����������ǂ���
	bool isLeft;									//���̕ǂɓ����������ǂ���
	static constexpr float moveSpeed = 2.0f;		//�v���C���[�̈ړ����x�ړ����x

	bool isGround;									//�n�ʂɗ����Ă��邩
	bool isJump;									//�W�����v�������ǂ���
	bool isMove;									//�����Ă��邩
	bool isWallRun;									//�E�H�[���������Ă��邩�ǂ���
	bool isWallJump;								//�ǃW�����v�������ǂ���
	float gravity;									//�v���C���[�ɂ�����d�͗�
	static constexpr float addGravity = 0.1f;		//�d�͉��Z��
	static constexpr float maxGravity = 3.0f;		//�ő�d�͗�

	float jump;										//�W�����v��
	static constexpr float jumpPower = 4.5f;		//�W�����v�͉��Z��

	static VECTOR angle;							//�v���C���[�̌���
	VECTOR jumpAngle;								//�W�����v�����Ƃ��̌���
	static constexpr float directionSpeed = 0.1f;	//�v���C���[�̕����]�����x

	static const VECTOR fixAngle;				//���f���̕����C��

	int animationIndex;								//�A�j���[�V�����ԍ�
	float totalAnimTime;							//�A�j���[�V�����̑��Đ�����
	float playAnimTime;								//�A�j���[�V�����̍Đ�����
	static constexpr float animationSpeed = 1.0f;	//�A�j���[�V�����Đ����x

	static VECTOR headPos;						//���̃t���[���̍��W
	static constexpr int headFrameIndex = 5;	//���̃t���[���̔ԍ�

	static constexpr int lineNum = 2;				//������2�_
	static constexpr int lineDivNum = 5;			//�����蔻��p�����̗�

	static constexpr float groundLineWidth = 5.0f;		//�n�ʓ����蔻������̒���
	static constexpr float groundLineSpace = 0.75f;		//�n�ʓ����蔻������̊Ԋu

	VECTOR groundLinePos[lineDivNum][lineDivNum];			//�n�ʂ̓����蔻��p�����̍��W

	static constexpr float wallCollisionLineWidth = 7.5f;	//�ǂ̓����蔻������̒���
	static constexpr float wallCollisionLineSpace = 7.5f;	//�ǂ̓����蔻������̊��o
	static constexpr float fixWallCollisionLinePosY = 12.0f;	//�ǂ̓����蔻�������Y���W������

	VECTOR wallCollisionLinePos[lineNum][lineDivNum][lineDivNum];	//�ǂƂ̓����蔻��p�����̍��W
	VECTOR sideCollisionLinePos[lineNum][lineDivNum][lineDivNum];	//���ʂ̓����蔻��p�����̍��W

	static constexpr int jumpButtonIndex = 12;		//�W�����v�{�^���̔ԍ�
};


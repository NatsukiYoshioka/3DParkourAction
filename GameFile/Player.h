#pragma once
#include<vector>

using namespace std;

class GameObject;
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
		STANDING_TO_CROUCH			//�������炵�Ⴊ��
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
	/// �I�u�W�F�N�g�̕`��
	/// </summary>
	void Draw();

private:
	vector<int> animationHandle;		//�A�j���[�V�����̔z��
	STATUS status;						//�v���C���[�̏��
};


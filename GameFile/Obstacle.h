#pragma once
#include"ObjectTag.h"
#include<DxLib.h>

class GameObject;

/// <summary>
/// ��Q���I�u�W�F�N�g�N���X
/// </summary>
class Obstacle:public GameObject
{
public:
	/// <summary>
	/// �I�u�W�F�N�g�̐���
	/// </summary>
	/// <param name="modelHandle">���f���n���h��</param>
	/// <param name="pos">�I�u�W�F�N�g�̍��W</param>
	/// <param name="angle">�I�u�W�F�N�g�̊p�x</param>
	/// <param name="isSlide">������邩�ǂ���</param>
	Obstacle(int modelHandle, VECTOR pos, float angle, int isSlide);

	/// <summary>
	/// �f�[�^�̉��
	/// </summary>
	~Obstacle();

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V
	/// </summary>
	void Update(GameManager::SCENE nowScene);

	/// <summary>
	/// �I�u�W�F�N�g�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���f���n���h���擾
	/// </summary>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle() { return modelHandle; }

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
	VECTOR angle;

	static const VECTOR scale;				//���f���̃X�P�[��

	static constexpr int frameIndex = -1;		//���f���̃t���[���̔ԍ�
	static constexpr int collisionDivNum = 2;	//�����蔻�蕪����
};


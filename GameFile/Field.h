#pragma once
#include"ObjectTag.h"
#include<DxLib.h>

class GameObject;

/// <summary>
/// �t�B�[���h�I�u�W�F�N�g�N���X
/// </summary>
class Field:public GameObject
{
public:
	/// <summary>
	/// ���f���̎擾�ƍ��W�Ɗp�x�̏�����
	/// </summary>
	/// <param name="modelHandle">���f���n���h��</param>
	/// <param name="pos">�I�u�W�F�N�g�̍��W</param>
	Field(int modelHandle, VECTOR pos,float angle);

	/// <summary>
	/// �f�[�^�̉��
	/// </summary>
	~Field();

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �I�u�W�F�N�g�̕`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���f���n���h���̎擾
	/// </summary>
	/// <returns>���f���n���h��</returns>
	int GetModelHandle() { return modelHandle; }

	/// <summary>
	/// �I�u�W�F�N�g�̃^�O�擾
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

	static constexpr int frameIndex = -1;
	static constexpr int collisionDivNum = 10;
};


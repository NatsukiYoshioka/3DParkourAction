#pragma once
#include<DxLib.h>

class GameObject;

/// <summary>
/// �t�B�[���h�I�u�W�F�N�g�N���X
/// </summary>
class Field:public GameObject
{
public:
	/// <summary>
	/// ���f���̎擾�ƍ��W�̏�����
	/// </summary>
	/// <param name="modelHandle">���f���n���h��</param>
	/// <param name="pos">�I�u�W�F�N�g�̍��W</param>
	Field(int modelHandle, VECTOR pos);

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

private:

};


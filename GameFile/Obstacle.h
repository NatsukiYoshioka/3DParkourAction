#pragma once
#include<DxLib.h>

class GameObject;

/// <summary>
/// ��Q���I�u�W�F�N�g�N���X
/// </summary>
class Obstacle:public GameObject
{
public:
	/// <summary>
	/// ���f���̎擾�ƍ��W�̏�����
	/// </summary>
	/// <param name="modelHandle">���f���n���h��</param>
	/// <param name="pos">�I�u�W�F�N�g�̍��W</param>
	Obstacle(int modelHandle, VECTOR pos);

	/// <summary>
	/// �f�[�^�̉��
	/// </summary>
	~Obstacle();

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


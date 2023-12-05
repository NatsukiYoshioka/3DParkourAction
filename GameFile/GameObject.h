#pragma once
#include"DxLib.h"

/// <summary>
/// �S�ẴQ�[���I�u�W�F�N�g�̊��N���X
/// </summary>
class GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameObject();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameObject();

	//�������z�֐�
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//�I�u�W�F�N�g�̓����蔻��
	virtual void OnCollisionEnter(const GameObject* other){}

	//���f���̎擾
	virtual int GetModelHandle() = 0;
protected:
	int modelHandle;			//���f���̃n���h��
	VECTOR pos;					//�I�u�W�F�N�g�̍��W
};


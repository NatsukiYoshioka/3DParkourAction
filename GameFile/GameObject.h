#pragma once
#include"ObjectTag.h"
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
	virtual void OnCollisionEnter(GameObject* other, const ObjectTag tag) {}

	//���f���̎擾
	virtual int GetModelHandle() = 0;
	//�^�O�̎擾
	virtual ObjectTag GetObjectTag() = 0;
	//���W�̎擾
	virtual VECTOR GetPos() = 0;
protected:
	ObjectTag tag;				//�I�u�W�F�N�g�̃^�O
	int modelHandle;			//���f���̃n���h��
	VECTOR pos;					//�I�u�W�F�N�g�̍��W
};


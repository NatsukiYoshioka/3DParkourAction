#pragma once
#include<string>
#include<vector>

using namespace std;

/// <summary>
/// �Q�[���ɕK�v�ȃf�[�^�����[�h����N���X
/// </summary>
class Load
{
private:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Load();

	/// <summary>
	/// �i�[�����f�[�^�̉��
	/// </summary>
	~Load();

public:
	/// <summary>
	/// �C���X�^���X�̐���
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �C���X�^���X�̔j��
	/// </summary>
	static void DestroyInstance();

	/// <summary>
	/// �C���X�^���X�擾
	/// </summary>
	/// <returns>�N���X�̃C���X�^���X</returns>
	static Load* GetInstance() { return load; }

	/// <summary>
	/// �t�@�C������f�[�^�̃p�X���擾
	/// </summary>
	/// <param name="filepath">csv�t�@�C���̃p�X</param>
	/// <param name="isHeader">�w�b�_�[�����邩�ǂ���</param>
	/// <param name="isIndex">�C���f�b�N�X�����邩�ǂ���</param>
	void ReadFile(string filepath, bool isHeader, bool isIndex);

	/// <summary>
	/// �f�[�^�̃��[�h
	/// </summary>
	void LoadData();

	/// <summary>
	/// �v���C���[�̃��f���n���h���擾
	/// </summary>
	/// <returns>�v���C���[���f���n���h��</returns>
	int GetPlayerModelHandle() { return playerModelHandle; }

	/// <summary>
	/// �t�B�[���h�̃��f���n���h���擾
	/// </summary>
	/// <returns>�t�B�[���h���f���n���h��</returns>
	vector<int> GetFieldModelHandle() { return fieldModelHandle; }

	/// <summary>
	/// ��Q���̃��f���n���h���擾
	/// </summary>
	/// <returns>��Q���̃��f���n���h��</returns>
	vector<int> GetObstacleModelHandle() { return obstacleModelHandle; }

private:
	static Load* load;				//���[�h�N���X�̃C���X�^���X

	string filePath;					//�Q�[���ɕK�v�ȃf�[�^�̃p�X���������t�@�C���̃p�X
	bool isHeader;						//�w�b�_�[�����邩�ǂ���
	bool isIndex;						//�C���f�b�N�X�����邩�ǂ���
	static constexpr char delim = ',';	//��؂�̕���

	vector<string> header;				//�w�b�_�[���ۊ�
	vector<string> index;				//�C���f�b�N�X���ۊ�
	vector<vector<string>> cell;				//�v�f�ۊ�

	int playerModelHandle;				//�v���C���[�̃��f���n���h��
	vector<int> fieldModelHandle;		//�t�B�[���h�̃��f���n���h��
	vector<float> fieldPosX;			//�t�B�[���h���f���̊e���W
	vector<float> fieldPosY;
	vector<float> fieldPosZ;
	vector<int> obstacleModelHandle;	//��Q���̃��f���n���h��
	vector<float> obstaclePosX;			//��Q���̊e���W
	vector<float> obstaclePosY;
	vector<float> obstaclePosZ;

	static constexpr const char* playerHeader = "PLAYER";
	static constexpr const char* fieldHeader = "FIELD";
	static constexpr const char* fieldPosXHeader = "FieldPosX";
	static constexpr const char* fieldPosYHeader = "FieldPosY";
	static constexpr const char* fieldPosZHeader = "FieldPosZ";
	static constexpr const char* obstacleHeader = "OBSTACLE";
	static constexpr const char* obstaclePosXHeader = "ObstaclePosX";
	static constexpr const char* obstaclePosYHeader = "ObstaclePosY";
	static constexpr const char* obstaclePosZHeader = "ObstaclePosZ";
};


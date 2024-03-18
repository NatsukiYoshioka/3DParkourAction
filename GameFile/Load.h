#pragma once
#include<string>
#include<vector>
#include<DxLib.h>

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
	/// �v���C���[�̃A�j���[�V�����擾
	/// </summary>
	/// <returns>�A�j���[�V������vector�z��</returns>
	vector<int> GetPlayerAnimationHandle() { return playerAnimationHandle; }

	/// <summary>
	/// �t�B�[���h�̃��f���n���h���擾
	/// </summary>
	/// <returns>�t�B�[���h���f���n���h����vector�z��</returns>
	vector<int> GetFieldModelHandle() { return fieldModelHandle; }

	/// <summary>
	/// �t�B�[���h�̍��W�擾
	/// </summary>
	/// <returns>�t�B�[���h���W��vector�z��</returns>
	vector<VECTOR> GetFieldPos() { return fieldPos; }

	/// <summary>
	/// �t�B�[���h�̊p�x�擾
	/// </summary>
	/// <returns>�t�B�[���h�p�x��vector�z��</returns>
	vector<float> GetFieldAngle() { return fieldAngle; }

	/// <summary>
	/// ��Q���̃��f���n���h���擾
	/// </summary>
	/// <returns>��Q���̃��f���n���h����vector�z��</returns>
	vector<int> GetObstacleModelHandle() { return obstacleModelHandle; }

	/// <summary>
	/// ��Q���̍��W�擾
	/// </summary>
	/// <returns>��Q���̍��W��vector�z��</returns>
	vector<VECTOR> GetObstaclePos() { return obstaclePos; }

	/// <summary>
	/// ��Q���̊p�x�擾
	/// </summary>
	/// <returns>��Q���̊p�x��vector�z��</returns>
	vector<float> GetObstacleAngle() { return obstacleAngle; }

	/// <summary>
	/// ��Q����������邩�ǂ����擾
	/// </summary>
	/// <returns>��Q����������邩�ǂ���</returns>
	vector<int> GetObstacleType() { return obstacleType; }

	/// <summary>
	/// �X�J�C�h�[���̃��f���n���h���擾
	/// </summary>
	/// <returns>�X�J�C�h�[���̃��f���n���h����vector�z��</returns>
	vector<int> GetSkydomeModelHandle() { return skydomeModelHandle; }

	/// <summary>
	/// �X�J�C�h�[���̍��W�擾
	/// </summary>
	/// <returns>�X�J�C�h�[�����W��vector�z��</returns>
	vector<VECTOR> GetSkydomePos() { return skydomePos; }

	/// <summary>
	/// UI�e�N�X�`���n���h���̎擾
	/// </summary>
	/// <returns>UI�e�N�X�`���n���h����vector�z��</returns>
	vector<int> GetUITextureHandle() { return UITextureHandle; }

	/// <summary>
	/// UI�̍��W�擾
	/// </summary>
	/// <returns>UI���W��vector�z��</returns>
	vector<VECTOR> GetUIPos() { return UIPos; }

	/// <summary>
	/// UI��`�悷��^�C�~���O���擾
	/// </summary>
	/// <returns>UI��`�悷��^�C�~���O��ۑ�����vector�z��</returns>
	vector<int> GetUIDrawTiming() { return UIDrawTiming; }

	/// <summary>
	/// �t�H���g�p�X�擾
	/// </summary>
	/// <returns>�t�H���g�p�X��vector�z��</returns>
	vector<string> GetFontPath(){return fontPath;}

private:
	static Load* load;				//���[�h�N���X�̃C���X�^���X

	string filePath;					//�Q�[���ɕK�v�ȃf�[�^�̃p�X���������t�@�C���̃p�X
	bool isHeader;						//�w�b�_�[�����邩�ǂ���
	bool isIndex;						//�C���f�b�N�X�����邩�ǂ���
	static constexpr char delim = ',';	//��؂�̕���

	vector<string> header;				//�w�b�_�[���ۊ�
	vector<string> index;				//�C���f�b�N�X���ۊ�
	vector<vector<string>> cell;		//�v�f�ۊ�

	int playerModelHandle;				//�v���C���[�̃��f���n���h��
	vector<int> playerAnimationHandle;	//�v���C���[�̃A�j���[�V�����n���h��

	vector<int> fieldModelHandle;		//�t�B�[���h�̃��f���n���h��
	int tempFieldModelHandle;			//�t�B�[���h���f�������ǉ��p���ۑ�
	vector<VECTOR> fieldPos;			//�t�B�[���h���f���̊e���W
	vector<float> fieldAngle;			//�t�B�[���h���f���̊p�x

	vector<int> obstacleModelHandle;	//��Q���̃��f���n���h��
	int tempObstacleModelHandle;		//��Q�����f�������ǉ��p���ۑ�
	vector<VECTOR> obstaclePos;			//��Q���̊e���W
	vector<float> obstacleAngle;		//��Q���̊p�x
	vector<int> obstacleType;			//��Q���̎��

	vector<int> skydomeModelHandle;		//�X�J�C�h�[���̃��f���n���h��
	vector<VECTOR> skydomePos;			//�X�J�C�h�[���̃|�W�V����

	vector<int> UITextureHandle;		//UI�摜�n���h��
	int tempUITextureHandle;			//UI���ۑ��p�n���h��
	vector<VECTOR> UIPos;				//UI���W
	vector<int> UIDrawTiming;			//UI��`�悷��^�C�~���O

	vector<string> fontPath;            //�t�H���g�p�X

	//�O���t�@�C�����̃w�b�_�[��
	static constexpr const char* playerHeader = "PLAYER";
	static constexpr const char* animationHeader = "ANIMATION";
	static constexpr const char* fieldHeader = "FIELD";
	static constexpr const char* fieldPosXHeader = "FieldPosX";
	static constexpr const char* fieldAngleHeader = "FieldAngle";
	static constexpr const char* obstacleHeader = "OBSTACLE";
	static constexpr const char* obstaclePosXHeader = "ObstaclePosX";
	static constexpr const char* obstacleAngleHeader = "ObstacleAngle";
	static constexpr const char* obstacleObstacleTypeHeader = "ObstacleType";
	static constexpr const char* skydomeHeader = "SKYDOME";
	static constexpr const char* skydomePosXHeader = "SkydomePosX";
	static constexpr const char* UIHeader = "UI";
	static constexpr const char* UIPosXHeader = "UIPosX";
	static constexpr const char* UIDrawTimingHeader = "DrawTiming";
	static constexpr const char* fontHeader="FONT";
};


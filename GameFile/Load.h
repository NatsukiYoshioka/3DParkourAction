#pragma once

using namespace std;

class Load
{
public:
	Load();

	string CastCell(string str) { return str; }
	void ReadFile(string, bool, bool);
	void LoadModel();
private:
	string filePath;
	bool isHeader;
	bool isIndex;
	static constexpr char delim = ',';

	//�w�b�_�[���ۊ�
	vector<string> header;
	//�C���f�b�N�X���ۊ�
	vector<string> index;
	//�v�f�ۊ�
	vector<vector<string>> cell;
};


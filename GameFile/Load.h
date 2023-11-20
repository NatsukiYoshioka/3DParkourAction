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

	//ヘッダー名保管
	vector<string> header;
	//インデックス名保管
	vector<string> index;
	//要素保管
	vector<vector<string>> cell;
};


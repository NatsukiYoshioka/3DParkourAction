#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include"common.h"
#include "Load.h"

Load::Load():
	isHeader(false),
	isIndex(false)
{

}

void Load::ReadFile(string filePath, bool isHeader, bool isIndex)
{
	this->filePath = filePath;
	this->isHeader = isHeader;
	this->isIndex = isIndex;

	string buf;
	string commaBuf;

	//“Ç‚İ‚Şcsvƒtƒ@ƒCƒ‹‚ğŠJ‚­
	ifstream file(this->filePath);

	//getlineŠÖ”‚Å1s‚¸‚Â“Ç‚İ‚ñ‚Åbuf‚ÉŠi”[
	for (int i = initializeNum; getline(file, buf); i++)
	{
		cell.push_back(vector<string>());

		//delim‹æØ‚è‚²‚Æ‚Éƒf[ƒ^‚ğ“Ç‚İ‚Ş‚½‚ß‚Éistringstream‚É‚·‚é
		istringstream iStream(buf);

		for (int j = initializeNum; getline(iStream, commaBuf, delim); j++)
		{
			if (this->isHeader && this->isIndex)
			{
				if (i == initializeNum && j == initializeNum)continue;
				//ƒwƒbƒ_[î•ñ‚ÌŠi”[
				if (i == initializeNum && j != initializeNum)header.push_back(commaBuf);
				//ƒCƒ“ƒfƒbƒNƒXî•ñ‚ÌŠi”[
				if (i != initializeNum && j == initializeNum)index.push_back(commaBuf);
				//—v‘f‚ÌŠi”[
				if (i != initializeNum && j != initializeNum)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else if (this->isHeader)
			{
				//ƒwƒbƒ_[î•ñ‚ÌŠi”[
				if (i == 0)header.push_back(commaBuf);
				//ƒCƒ“ƒfƒbƒNƒXî•ñ‚ÌŠi”[
				if (i != 0 && j == 0)index.push_back(string());
				//—v‘f‚ÌŠi”[
				if (i != 0)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else if (this->isIndex)
			{
				//ƒwƒbƒ_[î•ñ‚ÌŠi”[
				if (i == 0 && j != 0)header.push_back(string());
				//ƒCƒ“ƒfƒbƒNƒXî•ñ‚ÌŠi”[
				if (j == 0)index.push_back(commaBuf);
				//—v‘f‚ÌŠi”[
				if (j != 0)cell.at(i - 1).push_back(CastCell(commaBuf));
			}
			else
			{
				//ƒwƒbƒ_[î•ñ‚ÌŠi”[
				if (i == 0)header.push_back(string());
				//ƒCƒ“ƒfƒbƒNƒXî•ñ‚ÌŠi”[
				if (j == 0)index.push_back(string());
				//—v‘f‚ÌŠi”[
				cell.at(i).push_back(CastCell(commaBuf));
			}
		}
	}
}

void Load::LoadModel()
{
	for (int i = 0; i < index.size(); i++)
	{
		for (int j=0; header.size(); j++)
		{
			if (header.at(j) == "PLAYER")
			{

			}
		}
	}
}
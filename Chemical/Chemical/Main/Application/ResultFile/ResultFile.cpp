/**
 * @file	ResultFile.cpp
 * @brief	リザルトファイルクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultFile.h"

#include "Debugger\Debugger.h"
#include <string>


//----------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------
ResultFile::ResultFile()
{
}

ResultFile::~ResultFile()
{
}


//----------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------
bool ResultFile::Open()
{
	if (fopen_s(&m_pFile, "ResultFile", "a+") != 0)
	{
		OutputErrorLog(TEXT("ファイルの読み込み・生成に失敗しました。"));
		return false;
	}
	fscanf_s(m_pFile, "%d\n%d\n%d\n%d\n%d\n", &m_Seconds, &m_Minute, &m_Score, &m_IsClear, &m_StageNum);

	return true;
}

void ResultFile::Close()
{
	fclose(m_pFile);
}

void ResultFile::Write()
{
	std::string SecondsStr	= std::to_string(m_Seconds);
	std::string MinitueStr	= std::to_string(m_Minute);
	std::string ScoreStr	= std::to_string(m_Score);
	std::string ClearStr	= std::to_string(m_IsClear);
	std::string StageNumStr = std::to_string(m_StageNum);
	
	std::string Str = 
		SecondsStr	+ "\n" + 
		MinitueStr	+ "\n" + 
		ScoreStr	+ "\n" + 
		ClearStr	+ "\n" + 
		StageNumStr	+ "\n";

	freopen_s(&m_pFile, "ResultFile", "w", m_pFile);
	fprintf_s(m_pFile, "%s", Str.c_str());
}

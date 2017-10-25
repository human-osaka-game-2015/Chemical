/**
 * @file   GamePlayFile.cpp
 * @brief  GamePlayFileクラスの実装
 * @author kotani
 */
#include "GamePlayFile.h"

#include "Debugger\Debugger.h"
#include <string>


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool GamePlayFile::Open()
{
	if (fopen_s(&m_pFile, "GameFile", "a+") != 0)
	{
		OutputErrorLog(TEXT("ファイルの読み込み・生成に失敗しました。"));
		return false;
	}
	fscanf_s(m_pFile, "%d,", &m_SelectStageNum);

	return true;
}

void GamePlayFile::Close()
{
	fclose(m_pFile);
}

void GamePlayFile::Write()
{
	std::string str = std::to_string(m_SelectStageNum);

	freopen_s(&m_pFile, "GameFile", "w",m_pFile);
	fprintf_s(m_pFile, "%s", str.c_str());
}

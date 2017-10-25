/**
 * @file	CsvFile.cpp
 * @brief	CSVファイルクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "CsvFile.h"

#include <vector>


//----------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------
CsvFile::CsvFile()
{
}

CsvFile::CsvFile(LPCTSTR _pFilePath, int _lineNum)
{
	Load(_pFilePath, _lineNum);
}

CsvFile::~CsvFile()
{
	Release();
}


//----------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------
void CsvFile::Load(LPCTSTR _pFilePath, int _lineNum)
{
	std::vector<BYTE> MapData;

	FILE* pFile = nullptr;
	fopen_s(&pFile, _pFilePath, "r");

	// ファイルからデータを読み込む.
	{
		char Buffer[512];
		while (fgets(Buffer, _countof(Buffer), pFile))
		{
			char* pContext;
			char* pNext = strtok_s(Buffer, ",\n", &pContext);
			while (pNext)
			{
				MapData.push_back(atoi(pNext));
				pNext = strtok_s(nullptr, ",\n", &pContext);
			}
		}
	}

	// 読み込んだデータを詰める.
	{
		m_RowNum = MapData.size() / m_LineNum;
		m_ppData = new int*[m_LineNum];

		for (int i = 0; i < m_LineNum; i++)
		{
			m_ppData[i] = new int[m_RowNum];

			for (int j = 0; j < m_RowNum; j++)
			{
				m_ppData[i][j] = MapData[i * m_RowNum + j];
			}
		}
	}

	fclose(pFile);
}

void CsvFile::Release()
{
	for (int i = 0; i < m_LineNum; i++)
	{
		SafeDeleteArray(m_ppData[i]);
	}
	SafeDeleteArray(m_ppData);
}

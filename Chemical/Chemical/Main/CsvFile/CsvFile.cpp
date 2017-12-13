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
CsvFile::CsvFile() : 
	m_ppData(nullptr),
	m_LineNum(0),
	m_RowNum(0)
{
}

CsvFile::CsvFile(LPCTSTR _pFilePath)
{
	Load(_pFilePath);
}

CsvFile::~CsvFile()
{
	Release();
}


//----------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------
void CsvFile::Load(LPCTSTR _pFilePath)
{
	std::vector<int> MapData;

	FILE* pFile = nullptr;
	fopen_s(&pFile, _pFilePath, "r");

	// 改行をカウント.
	{
		char buf[1024];
		size_t ReadSize;

		while ((ReadSize = fread(buf, 1, 1024, pFile)) > 0)
		{
			for (size_t i = 0; i < ReadSize; i++)
			{
				if (buf[i] == '\n') m_LineNum++;
			}
		}
	}

	fseek(pFile, 0, FILE_BEGIN);

	// ファイルからデータを読み込む.
	{
		char Buffer[512];
		while (fgets(Buffer, _countof(Buffer), pFile))
		{
			char* pContext;
			char* pNext = strtok_s(Buffer, ",\n", &pContext);
			int A = *pNext;
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

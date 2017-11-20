/**
 * @file   InitializeData.cpp
 * @brief  クラスの実装
 * @author kotani
 */
#include "InitializeData.h"
#include "CsvFile\CsvFile.h"

#include "Debugger\Debugger.h"


namespace Game
{
	InitializeData::InitializeData()
	{
	}


	InitializeData::~InitializeData()
	{
	}

	void InitializeData::Load(int _stageNum)
	{
		float X = 120;
		float Y = 120;
		CsvFile* pCsvFile;

		// 入っているデータを確認して処理する.
		auto CheckData = [&](int _y, int _x)
		{
			switch (pCsvFile->GetData()[_y][_x])
			{
			case PLAYER:
				m_PlayerPos = D3DXVECTOR2(_x * X + X / 2, _y * Y + Y / 2);
				m_PlayerPos.y -= 60;
				break;
			case ENEMY:
				D3DXVECTOR2 tmp(_x * X + X / 2, _y * Y + Y / 2);
				tmp.y -= 60.f;
				m_EnemysPos.push_back(tmp);
				break;
			}
		};
		
		char FilePath[256];
		sprintf_s(FilePath, 256, "Resource\\GameScene\\CSV\\InitializeData_Stage%d.csv", _stageNum);
		pCsvFile = new CsvFile(FilePath);

		for (int i = 0; i < pCsvFile->GetLineNum(); i++)
		{
			for (int j = 0; j < pCsvFile->GetRowNum(); j++)
			{
				CheckData(i,j);
			}
		}

		SafeDelete(pCsvFile);
	}
}

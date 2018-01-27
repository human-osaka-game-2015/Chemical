/**
 * @file   InitializeFile.cpp
 * @brief  InitializeFileクラスの実装
 * @author kotani
 */
#include "InitializeFile.h"
#include "CsvFile\CsvFile.h"

#include "Debugger\Debugger.h"


namespace Game
{
	InitializeFile::InitializeFile(int _stageNum)
	{
		Load(_stageNum);
	}

	InitializeFile::~InitializeFile()
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------

	void InitializeFile::Load(int _stageNum)
	{
		float X = 120;
		float Y = 120;
		CsvFile* pCsvFile;

		// 入っているデータを確認して処理する.
		auto CheckData = [&](int _y, int _x)
		{
			switch (pCsvFile->GetData()[_y][_x])
			{
			case NONE:
				break;
			case PLAYER:
				m_PlayerInitPos = D3DXVECTOR2(_x * X + X / 2, _y * Y + Y / 2);
				m_PlayerInitPos.y -= 60;	// プレイヤーのサイズ分上にずらしている.
				break;
			default:
				D3DXVECTOR2 EnemyInitPos(_x * X + X / 2, _y * Y + Y / 2);
				EnemyInitPos.y -= 60.f;		// エネミーのサイズ分上にずらしている.
				m_EnemysInitPos.push_back(EnemyInitPos);
				m_EnemysPattern.push_back(pCsvFile->GetData()[_y][_x]);
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

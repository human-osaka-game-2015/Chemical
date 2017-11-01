/**
 * @file	StageChipManager.cpp
 * @brief	ステージチップ管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageChipManager.h"

#include "Application\GamePlayFile\GamePlayFile.h"
#include "CsvFile\CsvFile.h"
#include "StageChipBase\EmptyChip\EmptyChip.h"
#include "StageChipBase\SoilChip\SoilChip.h"
#include "StageChipBase\RoadChip\RoadChip.h"
#include "Debugger\Debugger.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Public Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 StageChipManager::m_DefaultChipSize = D3DXVECTOR2(80, 80);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageChipManager::StageChipManager() :
		m_pPlayFile(nullptr),
		m_pCsvFile(nullptr)
	{
		m_pChips[NONE_CHIP] = new EmptyChip();
		m_pChips[SOIL_CHIP] = new SoilChip();
		m_pChips[ROAD_CHIP] = new RoadChip();
	}

	StageChipManager::~StageChipManager()
	{
		for (int i = 0; i < STAGE_CHIP_MAX; i++)
		{
			SafeDelete(m_pChips[i]);
		}
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageChipManager::Initialize()
	{
		for (int i = 0; i < STAGE_CHIP_MAX; i++)
		{
			if (!m_pChips[i]->Initialize())	return false;
		}

		m_pPlayFile = new GamePlayFile();
		m_pPlayFile->Open();

		char FilePath[256];
		sprintf_s(
			FilePath, 
			256,
			"Resource\\GameScene\\CSV\\StageChip%d.csv", 
			m_pPlayFile->GetStageNum());
		m_pCsvFile = new CsvFile(FilePath);

		int LineNum = m_pCsvFile->GetLineNum();
		int RowNumNum = m_pCsvFile->GetRowNum();
		for (int i = 0; i < LineNum; i++)
		{
			for (int j = 0; j < RowNumNum; j++)
			{
				switch (m_pCsvFile->GetData()[i][j])
				{
				case NONE_CHIP:
					break;
				case SOIL_CHIP:
					m_pChips[SOIL_CHIP]->AddChip(j, i);
					break;
				case ROAD_CHIP:
					m_pChips[ROAD_CHIP]->AddChip(j, i);
					break;
				default:
					OutputErrorLog("StageChipのCSV内に不明なデータがあります");
					break;
				}
			}
		}

		for (int i = 0; i < STAGE_CHIP_MAX; i++)
		{
			if (!m_pChips[i]->CreateInstanceBuffer())	return false;
		}

		return true;
	}

	void StageChipManager::Finalize()
	{
		for (int i = 0; i < STAGE_CHIP_MAX; i++)
		{
			m_pChips[i]->ReleaseInstanceBuffer();
		}

		SafeDelete(m_pCsvFile);
		m_pPlayFile->Close();
		SafeDelete(m_pPlayFile);

		for (int i = 0; i < STAGE_CHIP_MAX; i++)
		{
			m_pChips[i]->Finalize();
		}
	}
}

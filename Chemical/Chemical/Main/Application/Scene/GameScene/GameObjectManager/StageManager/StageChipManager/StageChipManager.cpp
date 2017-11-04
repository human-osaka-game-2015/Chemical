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
#include "StageChipBase\Soil\SoilChip\SoilChip.h"
#include "StageChipBase\Soil\SoilGroundBottom\SoilGroundBottom.h"
#include "StageChipBase\Soil\SoilGroundBottomLeftSide\SoilGroundBottomLeftSide.h"
#include "StageChipBase\Soil\SoilGroundBottomRightSide\SoilGroundBottomRightSide.h"
#include "StageChipBase\Soil\SoilGroundTop\SoilGroundTop.h"
#include "StageChipBase\Soil\SoilGroundTopLeftSide\SoilGroundTopLeftSide.h"
#include "StageChipBase\Soil\SoilGroundTopRightSide\SoilGroundTopRightSide.h"
#include "Debugger\Debugger.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Public Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 StageChipManager::m_DefaultChipSize = D3DXVECTOR2(120, 120);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageChipManager::StageChipManager() :
		m_pPlayFile(nullptr),
		m_pCsvFile(nullptr)
	{
		m_pChips[NONE_CHIP] = new EmptyChip();
		m_pChips[SOIL_CHIP] = new SoilChip();
		m_pChips[SOIL_BOTTOM_CHIP] = new SoilGroundBottom();
		m_pChips[SOIL_BOTTOM_LEFT_CHIP] = new SoilGroundBottomLeftSide();
		m_pChips[SOIL_BOTTOM_RIGHT_CHIP] = new SoilGroundBottomRightSide();
		m_pChips[SOIL_TOP_CHIP] = new SoilGroundTop();
		m_pChips[SOIL_TOP_LEFT_CHIP] = new SoilGroundTopLeftSide();
		m_pChips[SOIL_TOP_RIGHT_CHIP] = new SoilGroundTopRightSide();
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
				// 取得したデータに対応したチップを追加.
				m_pChips[m_pCsvFile->GetData()[i][j]]->AddChip(j, i);
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

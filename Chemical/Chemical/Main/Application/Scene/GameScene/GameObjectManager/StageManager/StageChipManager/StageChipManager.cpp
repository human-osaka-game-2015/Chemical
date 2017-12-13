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
#include "StageChipBase\EmptyChip\EmptyChip.h"
#include "StageChipBase\Soil\Soil\Soil.h"
#include "StageChipBase\Soil\SoilBottom\SoilBottom.h"
#include "StageChipBase\Soil\SoilTop\SoilTop.h"
#include "StageChipBase\Rock\Rock\Rock.h"
#include "StageChipBase\Rock\RockBottom\RockBottom.h"
#include "StageChipBase\Rock\RockTop\RockTop.h"
#include "StageChipBase\Lava\Lava\Lava.h"
#include "StageChipBase\Lava\LavaBottom\LavaBottom.h"
#include "StageChipBase\Lava\LavaTop\LavaTop.h"
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
		m_pChips[SOIL_CHIP] = new Soil();
		m_pChips[SOIL_BOTTOM_CHIP] = new SoilBottom();
		m_pChips[SOIL_TOP_CHIP] = new SoilTop();
		m_pChips[ROCK_CHIP] = new Rock();
		m_pChips[ROCK_BOTTOM_CHIP] = new RockBottom();
		m_pChips[ROCK_TOP_CHIP] = new RockTop();
		m_pChips[LAVA_CHIP] = new Lava();
		m_pChips[LAVA_BOTTOM_CHIP] = new LavaBottom();
		m_pChips[LAVA_TOP_CHIP] = new LavaTop();
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
		m_pPlayFile->Close();	// 不必要なので閉じる.

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
		SafeDelete(m_pPlayFile);

		for (int i = 0; i < STAGE_CHIP_MAX; i++)
		{
			m_pChips[i]->Finalize();
		}
	}
}

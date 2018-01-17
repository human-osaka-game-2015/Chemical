/**
 * @file	StageGimmickManager.cpp
 * @brief	ステージギミック管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageGimmickManager.h"

#include "Application\GamePlayFile\GamePlayFile.h"
#include "StageGimmickBase\EmptyGimmick\EmptyGimmick.h"
#include "StageGimmickBase\FireGimmick\FireGimmick.h"
#include "StageGimmickBase\MushroomGimmick\MushroomGimmick.h"
#include "StageGimmickBase\WoodGimmick\WoodGimmick.h"
#include "StageGimmickBase\RecoveryGimmick\RecoveryGimmick.h"
#include "StageGimmickBase\EnemyGenerator\EnemyGenerator.h"
#include "StageGimmickBase\ButtonGimmick\ButtonGimmick.h"
#include "StageGimmickBase\GateGimmick\GateGimmick.h"
#include "StageGimmickBase\WarpGimmick\WarpEntranceGimmick\WarpEntranceGimmick.h"
#include "StageGimmickBase\WarpGimmick\WarpExitGimmick\WarpExitGimmick.h"
#include "StageGimmickBase\BeltConveyorGimmick\BeltConveyorGimmick\BeltConveyorGimmick.h"
#include "StageGimmickBase\BeltConveyorGimmick\BeltConveyorGimmickLeft\BeltConveyorGimmickLeft.h"
#include "StageGimmickBase\BeltConveyorGimmick\BeltConveyorGimmickRight\BeltConveyorGimmickRight.h"
#include "StageGimmickBase\RainCloud\RainCloud.h"
#include "StageGimmickBase\GateGimmick\GateGimmickLeft\GateGimmickLeft.h"
#include "StageGimmickBase\GateGimmick\GateGimmickRight\GateGimmickRight.h"
#include "StageGimmickBase\Block\BlueBlock\BlueBlock.h"
#include "StageGimmickBase\Block\RedBlock\RedBlock.h"
#include "StageGimmickBase\Block\BlueButtonGimmick\BlueButtonGimmick.h"
#include "StageGimmickBase\Block\RedButtonGimmick\RedButtonGimmick.h"
#include "Debugger\Debugger.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Public Variables
	//----------------------------------------------------------------------
	const D3DXVECTOR2 StageGimmickManager::m_DefaultGimmickSize = D3DXVECTOR2(120, 120);


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageGimmickManager::StageGimmickManager() :
		m_pPlayFile(nullptr),
		m_pCsvFile(nullptr)
	{
		m_pGimmicks[NONE_GIMMICK] = new EmptyGimmick();
		m_pGimmicks[FIRE_GIMMICK] = new FireGimmick();
		m_pGimmicks[MUSHROOM_GIMMICK] = new MushroomGimmick();
		m_pGimmicks[WOOD_GIMMICK]	= new WoodGimmick();
		m_pGimmicks[RECOVERY_GIMMICK] = new RecoveryGimmick();
		m_pGimmicks[ENEMY_GENERATOR_GIMMICK] = new EnemyGenerator();
		m_pGimmicks[BUTTON_GIMMICK] = new ButtonGimmick();
		m_pGimmicks[GATE_GIMMICK] = new GateGimmick();
		m_pGimmicks[WARP_ENTRANCE_GIMMICK] = new WarpEntranceGimmick();
		m_pGimmicks[WARP_EXIT_GIMMICK] = new WarpExitGimmick();
		m_pGimmicks[BELTCONVEYOR_GIMMICK] = new BeltConveyorGimmick();
		m_pGimmicks[BELTCONVEYOR_LEFT_GIMMICK] = new BeltConveyorGimmickLeft();
		m_pGimmicks[BELTCONVEYOR_RIGHT_GIMMICK] = new BeltConveyorGimmickRight();
		m_pGimmicks[RAINCLOUD_GIMMICK] = new RainCloud();
		m_pGimmicks[GATE_LEFT_GIMMICK] = new GateGimmickLeft();
		m_pGimmicks[GATE_RIGHT_GIMMICK] = new GateGimmickRight();
		m_pGimmicks[RED_BLOCK_GIMMICK] = new RedBlock();
		m_pGimmicks[BLUE_BLOCK_GIMMICK] = new BlueBlock();
		m_pGimmicks[RED_BUTTON_GIMMICK] = new RedButtonGimmick();
		m_pGimmicks[BLUE_BUTTON_GIMMICK] = new BlueButtonGimmick();
	}

	StageGimmickManager::~StageGimmickManager()
	{
		for (int i = 0; i < STAGE_GIMMICK_MAX; i++)
		{
			SafeDelete(m_pGimmicks[i]);
		}
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageGimmickManager::Initialize()
	{
		for (int i = 0; i < STAGE_GIMMICK_MAX; i++)
		{
			if (!m_pGimmicks[i]->Initialize())	return false;
		}

		m_pPlayFile = new GamePlayFile();
		m_pPlayFile->Open();

		char FilePath[256];
		sprintf_s(
			FilePath,
			256,
			"Resource\\GameScene\\CSV\\StageGimmick%d.csv",
			m_pPlayFile->GetStageNum());
		m_pPlayFile->Close();	// 不必要なので閉じる.

		m_pCsvFile = new CsvFile(FilePath);

		int LineNum = m_pCsvFile->GetLineNum();
		int RowNumNum = m_pCsvFile->GetRowNum();
		for (int i = 0; i < LineNum; i++)
		{
			for (int j = 0; j < RowNumNum; j++)
			{
				int Gimmick = m_pCsvFile->GetData()[i][j] / 100;
				int GimmickData = m_pCsvFile->GetData()[i][j] % 100;

				// 取得したデータに対応したチップを追加.
				m_pGimmicks[Gimmick]->AddGimmick(j, i, GimmickData);
			}
		}

		for (int i = 0; i < STAGE_GIMMICK_MAX; i++)
		{
			if (!m_pGimmicks[i]->CreateInstanceBuffer())	return false;
		}

		return true;
	}

	void StageGimmickManager::Finalize()
	{
		for (int i = 0; i < STAGE_GIMMICK_MAX; i++)
		{
			m_pGimmicks[i]->ReleaseInstanceBuffer();
		}

		SafeDelete(m_pCsvFile);
		SafeDelete(m_pPlayFile);

		for (int i = 0; i < STAGE_GIMMICK_MAX; i++)
		{
			m_pGimmicks[i]->Finalize();
		}
	}
}

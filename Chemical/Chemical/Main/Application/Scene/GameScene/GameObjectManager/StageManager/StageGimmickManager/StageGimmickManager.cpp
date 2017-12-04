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
				// 取得したデータに対応したチップを追加.
				m_pGimmicks[m_pCsvFile->GetData()[i][j]]->AddGimmick(j, i);
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

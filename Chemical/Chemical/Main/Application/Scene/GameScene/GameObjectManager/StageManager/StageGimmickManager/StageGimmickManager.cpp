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
		return true;
	}

	void StageGimmickManager::Finalize()
	{
	}
}

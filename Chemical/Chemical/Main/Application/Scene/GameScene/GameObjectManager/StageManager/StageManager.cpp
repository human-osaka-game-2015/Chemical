/**
 * @file	StageManager.cpp
 * @brief	ステージ管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "StageManager.h"

#include "Application\Application.h"
#include "StageBackground\StageBackground.h"
#include "StageChipManager\StageChipManager.h"
#include "StageGimmickManager\StageGimmickManager.h"
#include "..\GameDataManager\GameDataManager.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	StageManager::StageManager() :
		m_ScreenPos(D3DXVECTOR2(0, 0))
	{
		m_pObjects[STAGE_BACKGROUND] = new StageBackground();
		m_pObjects[STAGE_CHIP_MANAGER] = new StageChipManager();
		m_pObjects[STAGE_GIMMICK_MANAGER] = new StageGimmickManager();

		m_pUpdateTask = new Lib::UpdateTask();
	}

	StageManager::~StageManager()
	{
		delete m_pUpdateTask;

		delete m_pObjects[STAGE_GIMMICK_MANAGER];
		delete m_pObjects[STAGE_CHIP_MANAGER];
		delete m_pObjects[STAGE_BACKGROUND];
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool StageManager::Initialize()
	{
		for (int i = 0; i < STAGE_OBJECT_MAX; i++)
		{
			if (!m_pObjects[i]->Initialize()) return false;
		}

		StageChipManager* pStageChipManager = reinterpret_cast<StageChipManager*>(m_pObjects[STAGE_CHIP_MANAGER]);
		m_StageLine = pStageChipManager->GetLineNum();
		m_StageRow = pStageChipManager->GetRowNum();

		m_pUpdateTask->SetObject(this);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);

		SINGLETON_INSTANCE(GameDataManager)->SetScreenPosPtr(&m_ScreenPos);

		return true;
	}

	void StageManager::Finalize()
	{
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);

		for (int i = 0; i < STAGE_OBJECT_MAX; i++)
		{
			m_pObjects[i]->Finalize();
		}
	}

	void StageManager::Update()
	{
		D3DXVECTOR2 PlayerPos = SINGLETON_INSTANCE(GameDataManager)->GetPlayerPos();

		float X = static_cast<float>(Application::m_WindowWidth / 2);	//!< 画面中央からスクロール.
		if (PlayerPos.x > X)
			m_ScreenPos.x = PlayerPos.x - X;

		float Y = static_cast<float>(Application::m_WindowHeight);		//!< 画面下部からスクロール.
		if (PlayerPos.y > Y)
			m_ScreenPos.y = PlayerPos.y - Y;
	}
}

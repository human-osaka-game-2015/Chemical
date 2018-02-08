/**
 * @file	GameTimeManager.cpp
 * @brief	ゲーム内時間管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GameTimeManager.h"
#include "Application\Scene\GameScene\GameObjectManager\GameDataManager\GameDataManager.h"

#include "GameTimeUI\GameTimeUI.h"
#include "Debugger\Debugger.h"
#include "GameDefine.h"


namespace Game
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const int TimeManager::m_FrameMax = 60;
	const int TimeManager::m_SecondsMax = 60;
	const int TimeManager::m_MinuteMax = 99;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	TimeManager::TimeManager() : 
		m_Frame(0),
		m_Seconds(0),
		m_Minute(0)
	{
	}

	TimeManager::~TimeManager()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool TimeManager::Initialize()
	{
		m_pUpdateTask = new Lib::UpdateTask();
		m_pDrawTask = new Lib::Draw2DTask();

		m_pUpdateTask->SetObject(this);
		m_pDrawTask->SetObject(this);

		m_pDrawTask->SetPriority(GAME_DRAW_UI);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		m_pTimeUI = new TimeUI();
		if (!m_pTimeUI->Initialize())
		{
			return false;
		}

		return true;
	}

	void TimeManager::Finalize()
	{
		m_pTimeUI->Finalize();
		SafeDelete(m_pTimeUI);

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);

		SafeDelete(m_pDrawTask);
		SafeDelete(m_pUpdateTask);
	}

	void TimeManager::Update()
	{
		TimeUpdate();
		SINGLETON_INSTANCE(GameDataManager)->SetTime(m_Minute, m_Seconds);
		m_pTimeUI->SetFrame(m_Frame);
		m_pTimeUI->SetSeconds(m_Seconds);
		m_pTimeUI->SetMinute(m_Minute);
		m_pTimeUI->Update();
	}

	void TimeManager::Draw()
	{
		m_pTimeUI->Draw();
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void TimeManager::TimeUpdate()
	{
		m_Frame++;
		if (m_Frame < m_FrameMax) return;

		m_Frame = 0;
		m_Seconds++;
		if (m_Seconds < m_SecondsMax) return;

		m_Seconds = 0;
		m_Minute++;
		if (m_Minute < m_MinuteMax) return;
	}
}

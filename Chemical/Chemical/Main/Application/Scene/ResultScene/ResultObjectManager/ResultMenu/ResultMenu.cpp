/**
 * @file	ResultMenu.cpp
 * @brief	リザルトメニュークラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ResultMenu.h"

#include "..\..\ResultDefine.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "EventManager\EventManager.h"
#include "JoyconManager\JoyconManager.h"
#include "SoundManager\SoundManager.h"
#include "SoundManager\Sound\Sound.h"


namespace Result
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	ResultMenu::ResultMenu() : 
		m_IsSelected(true)
	{
		m_pBackButton		= new BackButton();
		m_pRestartButton	= new RestartButton();
		m_pRanking			= new Ranking();
		m_pResultScore		= new ResultScore();
		m_pResultTime		= new ResultTime();
		m_pEvent			= new ResultMenuEvent(RESULT_MENU_EVENT_ID);
		m_pEvent->SetType(ResultMenuEvent::STAGESELECT_BACK_EVENT);
	}

	ResultMenu::~ResultMenu()
	{
		SafeDelete(m_pEvent);
		SafeDelete(m_pResultTime);
		SafeDelete(m_pResultScore);
		SafeDelete(m_pRanking);
		SafeDelete(m_pRestartButton);
		SafeDelete(m_pBackButton);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool ResultMenu::Initialize()
	{
		m_pUpdateTask = new Lib::UpdateTask();
		m_pUpdateTask->SetObject(this);
		m_pUpdateTask->SetName("ResultMenu");
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);

		m_pBackButton->Initialize();
		m_pRestartButton->Initialize();
		m_pRanking->Initialize();
		m_pResultScore->Initialize();
		m_pResultTime->Initialize();

		SINGLETON_INSTANCE(Lib::SoundManager)->LoadSound(
			"Resource\\TitleScene\\Sound\\SelectSE.wav",
			&m_SelectSEIndex);

		SINGLETON_INSTANCE(Lib::SoundManager)->LoadSound(
			"Resource\\TitleScene\\Sound\\EnterSE.wav",
			&m_EnterSEIndex);

		return true;
	}

	void ResultMenu::Finalize()
	{
		SINGLETON_INSTANCE(Lib::SoundManager)->ReleaseSound(m_EnterSEIndex);
		SINGLETON_INSTANCE(Lib::SoundManager)->ReleaseSound(m_SelectSEIndex);

		m_pResultTime->Finalize();
		m_pResultScore->Finalize();
		m_pRanking->Finalize();
		m_pRestartButton->Finalize();
		m_pBackButton->Finalize();

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
		SafeDelete(m_pUpdateTask);
	}

	void ResultMenu::Update()
	{
		const Lib::KeyDevice::KEYSTATE* pKeyState = 
			SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();
		const Joycon::BUTTON_STATE* pRightButtonState =
			SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::RIGHT_CONTROLLER)->GetButtonState();
		const Joycon* pLeftJoycon =
			SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::LEFT_CONTROLLER);

		if (pKeyState[DIK_RIGHT] == Lib::KeyDevice::KEY_PUSH ||
			pLeftJoycon->GetAnalogStick().x > 0.5f)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			m_IsSelected = true;
			m_pBackButton->SetIsSelected(true);
			m_pRestartButton->SetIsSelected(false);
			m_pEvent->SetType(ResultMenuEvent::STAGESELECT_BACK_EVENT);
		}
		else if (pKeyState[DIK_LEFT] == Lib::KeyDevice::KEY_PUSH ||
			pLeftJoycon->GetAnalogStick().x < -0.5f)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			m_IsSelected = false;
			m_pBackButton->SetIsSelected(false);
			m_pRestartButton->SetIsSelected(true);
			m_pEvent->SetType(ResultMenuEvent::RESTART_EVENT);
		}

		if (pKeyState[DIK_SPACE] == Lib::KeyDevice::KEY_PUSH ||
			pRightButtonState[Joycon::A_BUTTON] == Joycon::PUSH_BUTTON)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_EnterSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_EnterSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(
				m_pEvent,
				TO_STRING(RESULT_MENU_EVENT_GROUP));
		}
	}

	void ResultMenu::Draw()
	{
	}
}

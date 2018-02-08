/**
 * @file   SelectManager.cpp
 * @brief  SelectManagerクラスの実装
 * @author kotani
 */
#include "SelectManager.h"
#include "../SelectObjectManager/SelectObjectManager.h"
#include "../SelectObjectManager/SelectBoard/SelectBoard.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "SoundManager\SoundManager.h"
#include "SoundManager\Sound\Sound.h"
#include "JoyconManager\JoyconManager.h"

namespace Select
{
	SelectManager::SelectManager() :
		m_SelectStageNumber(2),
		m_SelectState(STAGE_BOARD_SELECT)
	{
	}

	SelectManager::~SelectManager()
	{
	}

	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------
	bool SelectManager::Initialize()
	{
		SINGLETON_INSTANCE(Lib::SoundManager)->LoadSound(
			"Resource\\TitleScene\\Sound\\SelectSE.wav",
			&m_SelectSEIndex);

		SINGLETON_INSTANCE(Lib::SoundManager)->LoadSound(
			"Resource\\TitleScene\\Sound\\EnterSE.wav",
			&m_EnterSEIndex);
		return true;
	}

	void SelectManager::Finalize()
	{
		SINGLETON_INSTANCE(Lib::SoundManager)->ReleaseSound(m_EnterSEIndex);
		SINGLETON_INSTANCE(Lib::SoundManager)->ReleaseSound(m_SelectSEIndex);
	}

	void SelectManager::AddSelectBoard(SelectBoard* _pStageSelectBoard)
	{
		m_pSelectBoardList.push_back(_pStageSelectBoard);
	}

	void SelectManager::Update()
	{
		if (m_SelectState != STAGE_BOARD_SELECT) return;

		const Lib::KeyDevice::KEYSTATE* KeyState = SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();
		const Joycon::BUTTON_STATE* pRightButtonState =
			SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::RIGHT_CONTROLLER)->GetButtonState();
		const Joycon* pLeftJoycon =
			SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::LEFT_CONTROLLER);

		if ((KeyState[DIK_LEFT] == Lib::KeyDevice::KEY_PUSH) &&
			m_SelectStageNumber > 1)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			m_SelectStageNumber--;
		}
		else if (KeyState[DIK_UP] == Lib::KeyDevice::KEY_PUSH)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			m_SelectStageNumber -= 4;
			if (m_SelectStageNumber < 1)
			{
				m_SelectStageNumber = 1;
			}
		}
		else if (KeyState[DIK_DOWN] == Lib::KeyDevice::KEY_PUSH)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			m_SelectStageNumber += 4;
			if (m_SelectStageNumber > 8)
			{
				m_SelectStageNumber = 8;
			}
		}
		else if ((KeyState[DIK_RIGHT] == Lib::KeyDevice::KEY_PUSH) &&
			m_SelectStageNumber < 8)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_SelectSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			m_SelectStageNumber++;
		}

		if (KeyState[DIK_SPACE] == Lib::KeyDevice::KEY_PUSH || pRightButtonState[Joycon::A_BUTTON] == Joycon::PUSH_BUTTON)
		{
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_EnterSEIndex)->SoundOperation(
				Lib::SoundManager::STOP_RESET);
			SINGLETON_INSTANCE(Lib::SoundManager)->GetSound(m_EnterSEIndex)->SoundOperation(
				Lib::SoundManager::PLAY);
			m_pSelectBoardList[m_SelectStageNumber - 1]->Select();
			m_SelectState = STAGE_MENU_SELECT;
		}
		m_pSelectBoardList[m_SelectStageNumber - 1]->OnSelect();
	}
}

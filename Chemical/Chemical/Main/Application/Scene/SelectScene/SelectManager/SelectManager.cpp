/**
 * @file   SelectManager.cpp
 * @brief  SelectManagerクラスの実装
 * @author kotani
 */
#include "SelectManager.h"
#include "../SelectObjectManager/SelectObjectManager.h"
#include "../SelectObjectManager/SelectBoard/SelectBoard.h"
#include "InputDeviceManager\InputDeviceManager.h"

namespace Select
{
	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	void SelectManager::AddSelectBoard(SelectBoard* _pStageSelectBoard)
	{
		m_pSelectBoardList.push_back(_pStageSelectBoard);
	}

	void SelectManager::Update()
	{
		if (m_SelectState != STAGE_BOARD_SELECT) return;

		const Lib::KeyDevice::KEYSTATE* KeyState = SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();

		if (KeyState[DIK_LEFT] == Lib::KeyDevice::KEY_PUSH &&
			m_SelectStageNumber > 1)
		{
			m_SelectStageNumber--;
		}
		else if (KeyState[DIK_UP] == Lib::KeyDevice::KEY_PUSH)
		{
			m_SelectStageNumber -= 4;
			if (m_SelectStageNumber < 1)
			{
				m_SelectStageNumber = 1;
			}
		}
		else if (KeyState[DIK_DOWN] == Lib::KeyDevice::KEY_PUSH)
		{
			m_SelectStageNumber += 4;
			if (m_SelectStageNumber > 8)
			{
				m_SelectStageNumber = 8;
			}
		}
		else if (KeyState[DIK_RIGHT] == Lib::KeyDevice::KEY_PUSH &&
			m_SelectStageNumber < 8)
		{
			m_SelectStageNumber++;
		}

		if (KeyState[DIK_RETURN] == Lib::KeyDevice::KEY_PUSH)
		{
			m_pSelectBoardList[m_SelectStageNumber - 1]->Select();
			m_SelectState = STAGE_MENU_SELECT;
		}
		m_pSelectBoardList[m_SelectStageNumber - 1]->OnSelect();
	}
}

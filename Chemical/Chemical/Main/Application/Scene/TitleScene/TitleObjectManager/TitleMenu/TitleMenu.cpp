/**
 * @file	TitleMenu.cpp
 * @brief	タイトルメニュークラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "TitleMenu.h"

#include "..\..\TitleDefine.h"
#include "DirectX11\TextureManager\Dx11TextureManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "StartButton\StartButton.h"
#include "OptionButton\OptionButton.h"
#include "EndButton\EndButton.h"
#include "StaffButton\StaffButton.h"
#include "MenuCursorEvent\MenuCursorEvent.h"
#include "EventManager\EventManager.h"
#include "JoyconManager\JoyconManager.h"


namespace Title
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	Menu::Menu() :
		m_pUpdateTask(new Lib::UpdateTask()),
		m_pDrawTask(new Lib::Draw2DTask()),
		m_pEvent(new MenuCursorEvent(TITLE_MENU_EVENT)),
		m_IsMenuUp(false),
		m_IsUp(false),
		m_IsMenuDown(false),
		m_IsDown(false)
	{
		m_pMenuButtons[0] = new EndButton();
		m_pMenuButtons[1] = new StaffButton();
		m_pMenuButtons[2] = new OptionButton();
		m_pMenuButtons[3] = new StartButton();
	}

	Menu::~Menu()
	{
		for (auto& Button : m_pMenuButtons)
		{
			SafeDelete(Button);
		}

		SafeDelete(m_pEvent);
		SafeDelete(m_pDrawTask);
		SafeDelete(m_pUpdateTask);
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool Menu::Initialize()
	{
		m_pUpdateTask->SetObject(this);
		m_pDrawTask->SetObject(this);

		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->AddTask(m_pUpdateTask);
		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->AddTask(m_pDrawTask);

		for (auto& Button : m_pMenuButtons)
		{
			if (!Button->Initialize())	return false;
		}

		return true;
	}

	void Menu::Finalize()
	{
		for (auto& Button : m_pMenuButtons)
		{
			Button->Finalize();
		}

		SINGLETON_INSTANCE(Lib::Draw2DTaskManager)->RemoveTask(m_pDrawTask);
		SINGLETON_INSTANCE(Lib::UpdateTaskManager)->RemoveTask(m_pUpdateTask);
	}

	void Menu::Update()
	{
		const Lib::KeyDevice::KEYSTATE* pKeyState =
			SINGLETON_INSTANCE(Lib::InputDeviceManager)->GetKeyState();
		const Joycon::BUTTON_STATE* pRightButtonState = 
			SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::RIGHT_CONTROLLER)->GetButtonState();
		const Joycon* pLeftJoycon = 
			SINGLETON_INSTANCE(JoyconManager)->GetJoycon(Joycon::LEFT_CONTROLLER);

		if ((pKeyState[DIK_UP] == Lib::KeyDevice::KEY_ON ||
			pLeftJoycon->GetAnalogStick().y > 0.5f) &&
			m_IsMenuUp == false && m_IsMenuDown == false)
		{
			m_IsMenuUp = true;
			m_IsUp = true;
		}
		else if ((pKeyState[DIK_DOWN] == Lib::KeyDevice::KEY_ON ||
			pLeftJoycon->GetAnalogStick().y < -0.5f) &&
			m_IsMenuUp == false && m_IsMenuDown == false)
		{
			m_IsMenuDown = true;
			m_IsDown = true;
		}

		if ((pKeyState[DIK_SPACE] == Lib::KeyDevice::KEY_PUSH ||
			pRightButtonState[Joycon::A_BUTTON] == Joycon::PUSH_BUTTON) &&
			m_IsMenuUp == false && m_IsMenuDown == false)
		{
			// 一番前方にあるアイテムからイベントを取得.
			m_pEvent->SetEventType(m_pMenuButtons[3]->GetID());
			SINGLETON_INSTANCE(Lib::EventManager)->SendEventMessage(
				m_pEvent, 
				TO_STRING(TITLE_MENU_GROUP));
		}

		if (m_IsMenuUp)		MenuUp();
		if (m_IsMenuDown)	MenuDown();
	}

	void Menu::Draw()
	{
		for (auto& Button : m_pMenuButtons)
		{
			Button->Draw();
		}
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void Menu::MenuUp()
	{
		if (m_IsUp)
		{
			// 一番前方のアイテムを移動.
			if (m_pMenuButtons[3]->MoveUp())
			{
				m_IsUp = false;
				MenuButtonBase* pMenuButton = m_pMenuButtons[0];
				m_pMenuButtons[0] = m_pMenuButtons[3];
				m_pMenuButtons[3] = m_pMenuButtons[2];
				m_pMenuButtons[2] = m_pMenuButtons[1];
				m_pMenuButtons[1] = pMenuButton;
			}
		}
		else
		{
			bool IsRightMoveEnd = m_pMenuButtons[0]->MoveRight();
			bool IsRightCenterMoveEnd = m_pMenuButtons[1]->MoveRightCenter();
			bool IsLeftCenterMoveEnd = m_pMenuButtons[2]->MoveLeftCenter();
			bool IsLeftMoveEnd = m_pMenuButtons[3]->MoveLeft();

			if (IsRightMoveEnd)
			{
				bool IsDownMoveEnd = m_pMenuButtons[0]->MoveDown();
				if (IsDownMoveEnd && IsLeftCenterMoveEnd && IsRightCenterMoveEnd && IsLeftMoveEnd)
				{
					m_IsMenuUp = false;
				}
			}
		}
	}

	void Menu::MenuDown()
	{
		if (m_IsDown)
		{
			// 一番後方のアイテムを移動.
			if (m_pMenuButtons[0]->MoveUp())
			{
				m_IsDown = false;
				MenuButtonBase* pMenuButton = m_pMenuButtons[0];
				m_pMenuButtons[0] = m_pMenuButtons[1];
				m_pMenuButtons[1] = m_pMenuButtons[2];
				m_pMenuButtons[2] = m_pMenuButtons[3];
				m_pMenuButtons[3] = pMenuButton;
			}
		}
		else
		{
			bool IsRightMoveEnd = m_pMenuButtons[0]->MoveRight();
			bool IsRightCenterMoveEnd = m_pMenuButtons[1]->MoveRightCenter();
			bool IsLeftCenterMoveEnd = m_pMenuButtons[2]->MoveLeftCenter();
			bool IsLeftMoveEnd = m_pMenuButtons[3]->MoveLeft();

			if (IsLeftMoveEnd)
			{
				bool IsDownMoveEnd = m_pMenuButtons[3]->MoveDown();
				if (IsDownMoveEnd && IsRightMoveEnd && IsRightCenterMoveEnd && IsLeftCenterMoveEnd)
				{
					m_IsMenuDown = false;
				}
			}
		}
	}
}


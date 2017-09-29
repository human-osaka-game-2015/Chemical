/**
 * @file	GamePad.cpp
 * @brief	ゲームパッドクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "GamePad.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const float GamePad::m_ControlerDeadZone = 65535 / 4;


	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	GamePad::GamePad()
	{
		for (int count = 0; count < GAMEANALOG_MAX; count++)
		{
			for (int i = 0; i < XINPUT_ID_MAX; i++)
			{
				m_PadOldState[count][i] = PAD_OFF;
				m_PadState[count][i] = PAD_OFF;
			}
		}
	}

	GamePad::~GamePad()
	{
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	void GamePad::Update(XINPUTPAD _pad)
	{
		XINPUT_CAPABILITIES XInputCapabilities;
		if (XInputGetCapabilities(0, 0, &XInputCapabilities) == ERROR_DEVICE_NOT_CONNECTED)
		{
			return;
		}

		XInputGetState(_pad, &m_PadControlState[_pad].State);
	}

	void GamePad::CheckButton(XINPUTPAD _pad, XINPUT_ID _buttonId, WORD _xinputButton)
	{
		XINPUT_CAPABILITIES XInputCapabilities;
		if (XInputGetCapabilities(0, 0, &XInputCapabilities) == ERROR_DEVICE_NOT_CONNECTED)
		{
			return;
		}

		if (m_PadControlState[_pad].State.Gamepad.wButtons & _xinputButton)
		{
			if (m_PadOldState[_pad][_buttonId] == PAD_ON)
			{
				m_PadState[_pad][_buttonId] = PAD_ON;
			}
			else
			{
				m_PadState[_pad][_buttonId] = PAD_PUSH;
			}
			m_PadOldState[_pad][_buttonId] = PAD_ON;
		}
		else
		{
			if (m_PadOldState[_pad][_buttonId] == PAD_ON)
			{
				m_PadState[_pad][_buttonId] = PAD_RELEASE;
			}
			else
			{
				m_PadState[_pad][_buttonId] = PAD_OFF;
			}
			m_PadOldState[_pad][_buttonId] = PAD_OFF;
		}
	}

	GamePad::PADSTATE GamePad::GetButtonState(XINPUT_ID _buttonId, XINPUTPAD _pad)
	{
		return m_PadState[_pad][_buttonId];
	}

	bool GamePad::GetLAnalogState(ANALOGPAD _analogId, XINPUTPAD _pad)
	{
		switch (_analogId)
		{
		case ANALOG_LEFT:
			if (m_PadControlState[_pad].State.Gamepad.sThumbLX < -m_ControlerDeadZone)
			{
				return true;
			}
			break;
		case ANALOG_RIGHT:
			if (m_PadControlState[_pad].State.Gamepad.sThumbLX > m_ControlerDeadZone)
			{
				return true;
			}
			break;
		case ANALOG_UP:
			if (m_PadControlState[_pad].State.Gamepad.sThumbLY > m_ControlerDeadZone)
			{
				return true;
			}
			break;
		case ANALOG_DOWN:
			if (m_PadControlState[_pad].State.Gamepad.sThumbLY < -m_ControlerDeadZone)
			{
				return true;
			}
			break;
		}

		return false;
	}

	bool GamePad::GetRAnalogState(ANALOGPAD _analogId, XINPUTPAD _pad)
	{
		switch (_analogId)
		{
		case ANALOG_LEFT:
			if (m_PadControlState[_pad].State.Gamepad.sThumbRX < -m_ControlerDeadZone)
			{
				return true;
			}
			break;
		case ANALOG_RIGHT:
			if (m_PadControlState[_pad].State.Gamepad.sThumbRX > m_ControlerDeadZone)
			{
				return true;
			}
			break;
		case ANALOG_UP:
			if (m_PadControlState[_pad].State.Gamepad.sThumbRY > m_ControlerDeadZone)
			{
				return true;
			}
			break;
		case ANALOG_DOWN:
			if (m_PadControlState[_pad].State.Gamepad.sThumbRY < -m_ControlerDeadZone)
			{
				return true;
			}
			break;
		}

		return false;
	}
}


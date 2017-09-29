/**
 * @file	InputDeviceManager.cpp
 * @brief	入力デバイス管理クラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "InputDeviceManager.h"

#include "Debugger\Debugger.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	InputDeviceManager::InputDeviceManager() : 
		m_pGamePad(nullptr),
		m_pKeyDevice(nullptr),
		m_pMouseDevice(nullptr),
		m_pDInput8(nullptr),
		m_hWnd(nullptr)
	{
	}

	InputDeviceManager::~InputDeviceManager()
	{
		Finalize();
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool InputDeviceManager::Initialize(HWND _hWnd)
	{
		if (FAILED(DirectInput8Create(
			GetModuleHandle(nullptr),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			reinterpret_cast<void**>(&m_pDInput8),
			nullptr)))
		{
			OutputErrorLog("DirectInput8オブジェクトの生成に失敗しました");
			return false;
		}

		m_hWnd = _hWnd;

		return true;
	}

	void InputDeviceManager::Finalize()
	{
		SafeDelete(m_pGamePad);
		
		if (m_pKeyDevice != nullptr)
		{
			m_pKeyDevice->Finalize();
			SafeDelete(m_pKeyDevice);
		}

		if (m_pMouseDevice != nullptr)
		{
			m_pMouseDevice->Finalize();
			SafeDelete(m_pMouseDevice);
		}

		SafeRelease(m_pDInput8);
	}
	
	bool InputDeviceManager::CreateDevice(INPUTDEVICE_TYPE _deviceType, bool _isDebug, bool _IsPlayDebugLog)
	{
		bool Result = false;

		switch (_deviceType)
		{
		case GAMEPAD_TYPE:
			Result = CreateGamePad(_isDebug, _IsPlayDebugLog);
			break;
		case KEYDEVICE_TYPE:
			Result = CreateKeyDevice(_isDebug, _IsPlayDebugLog);
			break;
		case MOUSEDEVICE_TYPE:
			Result = CreateMouseDevice(_isDebug, _IsPlayDebugLog);
			break;
		}

		return Result;
	}

	void InputDeviceManager::ReleaseDevice(INPUTDEVICE_TYPE _deviceType)
	{
		switch (_deviceType)
		{
		case GAMEPAD_TYPE:
			ReleaseGamePad();
			break;
		case KEYDEVICE_TYPE:
			ReleaseKeyDevice();
			break;
		case MOUSEDEVICE_TYPE:
			ReleaseMouseDevice();
			break;
		}
	}

	void InputDeviceManager::KeyUpdate()
	{
		m_pKeyDevice->Update();
	}

	void InputDeviceManager::MouseUpdate()
	{
		m_pMouseDevice->Update();
	}

	void InputDeviceManager::GamePadUpdate(GamePad::XINPUTPAD _pad)
	{
		m_pGamePad->Update(_pad);
	}

	void InputDeviceManager::KeyCheck(int _dik)
	{
		m_pKeyDevice->KeyCheck(_dik);
	}

	void InputDeviceManager::CheckButton(GamePad::XINPUTPAD _pad, GamePad::XINPUT_ID _buttonId, WORD _button)
	{
		m_pGamePad->CheckButton(_pad, _buttonId, _button);
	}

	const KeyDevice::KEYSTATE* InputDeviceManager::GetKeyState() const
	{
		return m_pKeyDevice->GetKeyState();
	}

	const MouseDevice::MOUSESTATE InputDeviceManager::GetMouseState() const
	{
		return m_pMouseDevice->GetMouseState();
	}

	GamePad::PADSTATE InputDeviceManager::GetButtonState(GamePad::XINPUT_ID _buttonId, GamePad::XINPUTPAD _pad)
	{
		return m_pGamePad->GetButtonState(_buttonId, _pad);
	}

	bool InputDeviceManager::GetLAnalogState(GamePad::ANALOGPAD _analogId, GamePad::XINPUTPAD _pad)
	{
		return m_pGamePad->GetLAnalogState(_analogId, _pad);
	}

	bool InputDeviceManager::GetRAnalogState(GamePad::ANALOGPAD _analogId, GamePad::XINPUTPAD _pad)
	{
		return m_pGamePad->GetRAnalogState(_analogId, _pad);
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	bool InputDeviceManager::CreateGamePad(bool _isDebug, bool _IsPlayDebugLog)
	{
		if (m_pGamePad != nullptr)
		{
			OutputErrorLog("GamePadオブジェクトは既に生成されています");
			return false;
		}

		m_pGamePad = new GamePad();

		return true;
	}

	bool InputDeviceManager::CreateKeyDevice(bool _isDebug, bool _IsPlayDebugLog)
	{
		if (m_pKeyDevice != nullptr)
		{
			OutputErrorLog("KeyDeviceオブジェクトは既に生成されています");
			return false;
		}

		m_pKeyDevice = new KeyDevice();
		if (!m_pKeyDevice->Initialize(m_pDInput8, m_hWnd, _isDebug, _IsPlayDebugLog))
		{
			SafeDelete(m_pKeyDevice);
			return false;
		}

		return true;
	}

	bool InputDeviceManager::CreateMouseDevice(bool _isDebug, bool _IsPlayDebugLog)
	{
		if (m_pMouseDevice != nullptr)
		{
			OutputErrorLog("MouseDeviceオブジェクトは既に生成されています");
			return false;
		}

		m_pMouseDevice = new MouseDevice();
		if (!m_pMouseDevice->Initialize(m_pDInput8, m_hWnd))
		{
			SafeDelete(m_pMouseDevice);
			return false;
		}

		return true;
	}

	void InputDeviceManager::ReleaseGamePad()
	{ 
		SafeDelete(m_pGamePad);
	}

	void InputDeviceManager::ReleaseKeyDevice()
	{
		if (m_pKeyDevice != nullptr)
		{
			m_pKeyDevice->Finalize();
			SafeDelete(m_pKeyDevice);
		}
	}

	void InputDeviceManager::ReleaseMouseDevice()
	{
		if (m_pMouseDevice != nullptr)
		{
			m_pMouseDevice->Finalize();
			SafeDelete(m_pMouseDevice);
		}
	}
}

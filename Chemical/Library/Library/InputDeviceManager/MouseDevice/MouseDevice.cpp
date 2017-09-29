/**
 * @file	MouseDevice.cpp
 * @brief	マウスデバイス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "MouseDevice.h"

#include "..\..\Define\Define.h"
#include "..\..\Debugger\Debugger.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	MouseDevice::MouseDevice() : 
		m_pDInput8(nullptr), 
		m_pDInputDevice8(nullptr),
		m_hWnd(nullptr)
	{
	}

	MouseDevice::~MouseDevice()
	{
		Finalize();
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool MouseDevice::Initialize(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
	{
		MyAssert(_pDInput8 == nullptr, "DirectInputオブジェクトがありません");

		m_pDInput8 = _pDInput8;
		m_hWnd = _hWnd;

		if (FAILED(m_pDInput8->CreateDevice(GUID_SysMouse, &m_pDInputDevice8, nullptr)))
		{
			OutputErrorLog("DirectInputデバイスの生成に失敗しましたん");
			return false;
		}

		if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIMouse)))
		{
			OutputErrorLog("DirectInputデバイスのフォーマット失敗しましたん");
			SafeRelease(m_pDInputDevice8);
			return false;
		}

		DIPROPDWORD DiProp;
		DiProp.diph.dwSize = sizeof(DiProp);
		DiProp.diph.dwHeaderSize = sizeof(DiProp.diph);
		DiProp.diph.dwObj = 0;
		DiProp.diph.dwHow = DIPH_DEVICE;
		DiProp.dwData = 1000;
		if (FAILED(m_pDInputDevice8->SetProperty(DIPROP_BUFFERSIZE, &DiProp.diph)))
		{
			OutputErrorLog("DirectInputデバイスのプロパティ設定に失敗しましたん");
			SafeRelease(m_pDInputDevice8);
			return false;
		}

		if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		{
			OutputErrorLog("DirectInput協調レベルの設定に失敗しましたん");
			SafeRelease(m_pDInputDevice8);
			return false;
		}

		m_pDInputDevice8->Acquire();

		return true;
	}

	void MouseDevice::Finalize()
	{
		SafeRelease(m_pDInputDevice8);
	}

	void MouseDevice::Update()
	{
		HRESULT Result = m_pDInputDevice8->Acquire();
		if ((Result == DI_OK) || (Result == S_FALSE))
		{
			m_pDInputDevice8->GetDeviceState(sizeof(m_DIMouseState), &m_DIMouseState);
		}

		m_MouseState.lX = m_DIMouseState.lX;
		m_MouseState.lY = m_DIMouseState.lY;
		m_MouseState.lZ = m_DIMouseState.lZ;
		GetCursorPos(&m_MouseState.CursorPos);

		RECT WindowRect;
		GetWindowRect(m_hWnd, &WindowRect);
		m_MouseState.CursorPos.x -= WindowRect.left;
		m_MouseState.CursorPos.y -= WindowRect.top;

		for (int i = 0; i < 4; i++)
		{
			if (m_DIMouseState.rgbButtons[i])
			{
				if (m_OldDIMouseState.rgbButtons[i])
				{
					m_MouseState.Buttons[i] = MOUSEBUTTON_ON;
				}
				else
				{
					m_MouseState.Buttons[i] = MOUSEBUTTON_PUSH;
				}
				m_OldDIMouseState.rgbButtons[i] = m_DIMouseState.rgbButtons[i];
			}
			else
			{
				if (m_OldDIMouseState.rgbButtons[i])
				{
					m_MouseState.Buttons[i] = MOUSEBUTTON_RELEASE;
				}
				else
				{
					m_MouseState.Buttons[i] = MOUSEBUTTON_OFF;
				}
				m_OldDIMouseState.rgbButtons[i] = m_DIMouseState.rgbButtons[i];
			}
		}
	}
}


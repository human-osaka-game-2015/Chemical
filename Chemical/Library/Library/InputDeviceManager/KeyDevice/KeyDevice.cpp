/**
 * @file	KeyDevice.cpp
 * @brief	キーデバイスクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "KeyDevice.h"

#include "..\..\Define\Define.h"
#include "..\..\Debugger\Debugger.h"


namespace Lib
{
	//----------------------------------------------------------------------
	// Static Private Variables
	//----------------------------------------------------------------------
	const char* KeyDevice::m_pDebugFileName = "KeyLog.log";
	const int KeyDevice::m_DebugFileSizeMax = 50000000;
	const int KeyDevice::m_TimeCounterMax = 2000000000;
	const int KeyDevice::m_TimeCounter2Max = 2000000000;
	

	//----------------------------------------------------------------------
	// Constructor	Destructor
	//----------------------------------------------------------------------
	KeyDevice::KeyDevice() :
		m_pDInput8(nullptr),
		m_pDInputDevice8(nullptr),
		m_hWnd(nullptr),
		m_IsDebug(false),
		m_pDebugFile(nullptr),
		m_TimeCounter(0),
		m_TimeCounter2(0),
		m_IsDebugLogPlay(false)
	{
		m_pUpdateFunc = &KeyDevice::NormalUpdate;
	}

	KeyDevice::~KeyDevice()
	{
		Finalize();
	}


	//----------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------
	bool KeyDevice::Initialize(LPDIRECTINPUT8 _pDInput8, HWND _hWnd, bool _isDebug, bool _IsPlayDebugLog)
	{
		MyAssert(_pDInput8 == nullptr, "DirectInputオブジェクトがありません");

		m_pDInput8 = _pDInput8;
		m_hWnd = _hWnd;
		m_IsDebug = _isDebug;
		m_IsDebugLogPlay = _IsPlayDebugLog;


#ifdef _DEBUG
		// デバッグフラグで更新関数を変更.
		if (m_IsDebug && m_IsDebugLogPlay == false)
		{
			m_pUpdateFunc = &KeyDevice::DebugUpdate;
			fopen_s(&m_pDebugFile, m_pDebugFileName, "w");
		}
		else if (m_IsDebug && m_IsDebugLogPlay)
		{
			//m_pUpdateFunc = &KeyDevice::DebugLogPlay;
			//fopen_s(&m_pDebugFile, m_pDebugFileName, "r");
			///@todo デバッグログを再生する機能は未実装.
		}
#endif // _DEBUG


		if (FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard, &m_pDInputDevice8, nullptr)))
		{
			OutputErrorLog("デバイスの生成に失敗しました");
			return false;
		}

		if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIKeyboard)))
		{
			OutputErrorLog("デバイスのフォーマットに失敗しました");
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
			OutputErrorLog("デバイスのプロパティ設定に失敗しました");
			SafeRelease(m_pDInputDevice8);
			return false;
		}

		if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		{
			OutputErrorLog("デバイスの協調レベルの設定に失敗しました");
			SafeRelease(m_pDInputDevice8);
			return false;
		}

		m_pDInputDevice8->Acquire();

		return true;
	}

	void KeyDevice::Finalize()
	{
		SafeRelease(m_pDInputDevice8);

#ifdef _DEBUG
		if (m_IsDebug)
		{
			fclose(m_pDebugFile);
		}
#endif // _DEBUG
	}

	void KeyDevice::Update()
	{
		(this->*m_pUpdateFunc)();
	}

	void KeyDevice::KeyCheck(int _dik)
	{
		if (m_pDIKeyState[_dik] & 0x80)
		{
			if (m_pOldDIKeyState[_dik] == KEY_OFF)
			{
				m_pKeyState[_dik] = KEY_PUSH;
			}
			else
			{
				m_pKeyState[_dik] = KEY_ON;
			}
			m_pOldDIKeyState[_dik] = KEY_ON;
		}
		else
		{
			if (m_pOldDIKeyState[_dik] == KEY_ON)
			{
				m_pKeyState[_dik] = KEY_RELEASE;
			}
			else
			{
				m_pKeyState[_dik] = KEY_OFF;
			}
			m_pOldDIKeyState[_dik] = KEY_OFF;
		}
	}


	//----------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------
	void KeyDevice::NormalUpdate()
	{
		// キー情報の更新処理.
		HRESULT Result = m_pDInputDevice8->Acquire();
		if ((Result == DI_OK) || (Result == S_FALSE))
		{
			m_pDInputDevice8->GetDeviceState(sizeof(m_pDIKeyState), &m_pDIKeyState);
		}
	}

	void KeyDevice::DebugUpdate()
	{
		// キー情報の更新処理.
		HRESULT Result = m_pDInputDevice8->Acquire();
		if ((Result == DI_OK) || (Result == S_FALSE))
		{
			m_pDInputDevice8->GetDeviceState(sizeof(m_pDIKeyState), &m_pDIKeyState);
		}

		// 更新関数が実行されるたびにキー情報をファイルに出力.
		for (int i = 0; i < 256; i++)
		{
			if (m_pDIKeyState[i] & 0x80)
			{
				fprintf(m_pDebugFile, "%d,%d,%d,%d\n", i, m_pDIKeyState[i], m_TimeCounter, m_TimeCounter2);
			}
		}

		// タイムカウンタの処理.
		m_TimeCounter++;
		if (m_TimeCounter >= m_TimeCounterMax)
		{
			m_TimeCounter2++;
			if (m_TimeCounter2 >= m_TimeCounter2Max)
			{
				m_TimeCounter2 = 0;
				Debugger::OutputDebugLog("\n\nタイムカウンタが溢れました\n\n");
			}
			m_TimeCounter = 0;
		}

		// ファイルサイズのチェック.
		fpos_t FileSize;
		fgetpos(m_pDebugFile, &FileSize);
		if (FileSize >= m_DebugFileSizeMax)
		{
			Debugger::OutputDebugLog("\n\nデバッグログファイルが既定のサイズを超えました\n");
			Debugger::OutputDebugLog("\nファイルを破棄します\n\n");
			fclose(m_pDebugFile);
			fopen_s(&m_pDebugFile, m_pDebugFileName, "w");
		}
	}

	void KeyDevice::DebugLogPlay()
	{
		///@todo デバッグログ再生の更新関数は未実装.
	}
}

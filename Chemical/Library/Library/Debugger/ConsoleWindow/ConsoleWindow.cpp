/**
 * @file	ConsoleWindow.cpp
 * @brief	コンソールウィンドウクラス実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "ConsoleWindow.h"
#include "..\Debugger.h"
#include <stdio.h>


namespace Lib
{
	namespace Debugger
	{
		//----------------------------------------------------------------------
		// Static Public Variables
		//----------------------------------------------------------------------
		const int ConsoleWindow::m_OutputBufferSize = 512;


		//----------------------------------------------------------------------
		// Constructor	Destructor
		//----------------------------------------------------------------------
		ConsoleWindow::ConsoleWindow() :
			m_ReadHandle(nullptr),
			m_WriteHandle(nullptr),
			m_ProcessHandle(nullptr),
			m_IsActive(false)
		{
		}

		ConsoleWindow::~ConsoleWindow()
		{
		}


		//----------------------------------------------------------------------
		// Public Functions
		//----------------------------------------------------------------------
		bool ConsoleWindow::Initialize(LPCTSTR _name)
		{
#ifdef _DEBUG
			// パイプの作成.
			SECURITY_ATTRIBUTES SecurityAttribute;
			SecurityAttribute.nLength = sizeof(SECURITY_ATTRIBUTES);
			SecurityAttribute.bInheritHandle = 1;
			SecurityAttribute.lpSecurityDescriptor = 0;
			if (!CreatePipe(&m_ReadHandle, &m_WriteHandle, &SecurityAttribute, 0))
			{
				OutputDebugLog("無名パイプの作成に失敗しました");
				return false;
			}

			// 子プロセス書き込みハンドルを継承するように.
			SetHandleInformation(m_WriteHandle, HANDLE_FLAG_INHERIT, 0);

			// プロセスの作成.
			PROCESS_INFORMATION ProcessInfo;
			ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
			STARTUPINFO StartUpInfo;
			ZeroMemory(&StartUpInfo, sizeof(StartUpInfo));
			StartUpInfo.cb = sizeof(STARTUPINFO);
			StartUpInfo.hStdInput = m_ReadHandle;
			StartUpInfo.dwFlags |= STARTF_USESTDHANDLES;
			TCHAR Program[] = TEXT("Library\\Debugger\\DebugConsoleWindow.exe");
			TCHAR Args[64];
			sprintf_s(Args, "%s", _name);
			for (int i = 0; i < _countof(Args); i++)
			{
				// スペースがあると別引数と認識されるので-に置き換え.
				if (Args[i] == ' ')	Args[i] = '-';
			}

			if (!CreateProcess(
				Program,
				Args,
				0,
				0,
				true,
				CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
				0,
				0,
				&StartUpInfo,
				&ProcessInfo))
			{
				OutputDebugLog("プロセスの作成に失敗しました");
				return false;
			}

			m_ProcessHandle = ProcessInfo.hProcess;
			CloseHandle(ProcessInfo.hThread);	// プライマリスレッドのハンドルは必要ないので閉じる.

			m_IsActive = true;

#endif // _DEBUG

			return true;
		}

		void ConsoleWindow::Finalize()
		{
#ifdef _DEBUG
			if (!m_IsActive) return;

			if (m_WriteHandle != INVALID_HANDLE_VALUE)
			{
				if (m_ProcessHandle != INVALID_HANDLE_VALUE)
				{
					TerminateProcess(m_ProcessHandle, 0);	// プロセスの強制終了.
					CloseHandle(m_ProcessHandle);			// プロセスハンドルを閉じる.
				}
				CloseHandle(m_WriteHandle);
				CloseHandle(m_ReadHandle);
			}

			m_IsActive = false;

#endif // !_DEBUG
		}

		void ConsoleWindow::Print(LPCTSTR _pStr, ...)
		{
#ifdef _DEBUG
			if (!m_IsActive) return;

			if (WaitForSingleObject(m_ProcessHandle, 0) == WAIT_OBJECT_0)
			{
				Finalize();
				return;
			}

			TCHAR OutputStr[m_OutputBufferSize];
			va_list ArgsList;
			va_start(ArgsList, _pStr);
			vsprintf_s(OutputStr, sizeof(OutputStr), _pStr, ArgsList);
			va_end(ArgsList);

			DWORD Word;
			WriteFile(m_WriteHandle, OutputStr, strlen(OutputStr), &Word, 0);
#endif // _DEBUG
		}
	}
}

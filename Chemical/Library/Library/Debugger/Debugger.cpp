/**
 * @file	Debugger.cpp
 * @brief	デバッグ機能実装
 * @author	morimoto
 */

//----------------------------------------------------------------------
// Include
//----------------------------------------------------------------------
#include "Debugger.h"

#include <stdio.h>
#include <stdarg.h>


namespace Lib
{
	namespace Debugger
	{
#ifdef _DEBUG

		//----------------------------------------------------------------------
		// Static Variables
		//----------------------------------------------------------------------
		static const unsigned int	g_DebugLogMax = 512;	//!< デバッグログの最大文字数.
		static FILE*				g_pLogFile = nullptr;	//!< デバッグ用ファイルポインタ.
		static const int			g_StackMax = 100;		//!< 保持するスタックフレームの最大数.
		static const int			g_SymbolNameMax = 256;	//!< シンボル名の最大文字数.


		//----------------------------------------------------------------------
		// Functions
		//----------------------------------------------------------------------
		void CheckMemoryLeak()
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		}

		void OutputDebugLog(TCHAR* _pStr, ...)
		{
			TCHAR OutputStr[g_DebugLogMax];
			va_list ArgsList;

			va_start(ArgsList, _pStr);

			vsprintf_s(OutputStr, sizeof(OutputStr), _pStr, ArgsList);
			OutputDebugString(OutputStr);

			va_end(ArgsList);
		}

		void OpenLogFile(TCHAR* _pFilePath)
		{
			fopen_s(&g_pLogFile, _pFilePath, "w");
		}

		void WriteLogFile(TCHAR* _pStr, ...)
		{
			TCHAR OutputStr[g_DebugLogMax];
			va_list ArgsList;

			va_start(ArgsList, _pStr);

			vsprintf_s(OutputStr, sizeof(OutputStr), _pStr, ArgsList);
			fprintf(g_pLogFile, OutputStr);

			va_end(ArgsList);
		}

		void CloseLogFile()
		{
			fclose(g_pLogFile);
		}

		void OutputStackFrame()
		{
			// 現在のプロセスの擬似ハンドルを取得して初期化.
			HANDLE Process = GetCurrentProcess();	
			SymInitialize(Process, nullptr, TRUE);

			// スタック情報をキャプチャ.
			void* pStack[g_StackMax];
			USHORT Frames = CaptureStackBackTrace(0, g_StackMax, pStack, nullptr);

			// シンボル情報構造体を初期化.
			SYMBOL_INFO* pSymbol = reinterpret_cast<SYMBOL_INFO*>(calloc(sizeof(SYMBOL_INFO), Frames));
			pSymbol->MaxNameLen = g_SymbolNameMax;
			pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);

			OutputDebugLog("\n--------------------StackFrame--------------------\n\n");
			for (int i = 0; i < Frames; i++)
			{
				// シンボル情報取得.
				SymFromAddr(
					Process, 
					reinterpret_cast<DWORD64>(pStack[i]), 
					nullptr, 
					pSymbol);

				OutputDebugLog("Frame  : %i\n", Frames - i - 1);		// フレーム番号.
				OutputDebugLog("Name   : %s\n", pSymbol->Name);			// フレーム名.
				OutputDebugLog("Addres : 0x%0X\n", pSymbol->Address);	// フレームアドレス.
				OutputDebugLog("Size   : %lu\n\n", pSymbol->Size);		// フレームサイズ.
			}

			free(pSymbol);

			SymCleanup(Process); // プロセスの解放.
		}

#else // _DEBUG

		//----------------------------------------------------------------------
		// Functions
		//----------------------------------------------------------------------
		void CheckMemoryLeak()
		{
		}

		void OutputDebugLog(TCHAR* _pStr, ...)
		{
		}

		void OpenLogFile(TCHAR* _pFilePath)
		{
		}

		void WriteLogFile(TCHAR* _pStr, ...)
		{
		}

		void CloseLogFile()
		{
		}

		void StartTimer()
		{
		}

		void EndTimer()
		{
		}

		LONGLONG GetTime()
		{
			return 0;
		}

		void OutputStackFrame()
		{
		}

#endif // !_DEBUG
	}
}

